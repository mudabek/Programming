#!/usr/bin/env python3
from argparse import (ArgumentParser, ArgumentDefaultsHelpFormatter)
import xml.etree.ElementTree as ET
import json
import logging
import logging.config
import yaml
import re

APPLICATION_NAME = "stackoverflow_analytics"
APPLICATION_WARNINGS = "stackoverflow_analytics_warning"
DEFAULT_LOGGING_CONFIG_PATH = "logging.conf.yml"

logger = logging.getLogger(APPLICATION_NAME)
warn_logger = logging.getLogger(APPLICATION_WARNINGS)

def merge_two_dicts(dict1, dict2):
    merged = {k: dict1.get(k, 0) + dict2.get(k, 0) for k in set(dict1) | set(dict2)}
    return merged


def make_year_scores_dict(xml_filepath: str, stop_words_dict : dict):
    year_scores_dict = {}
    with open(xml_filepath, encoding = "utf-8") as file:
        whole_content = file.readlines()
        for content in whole_content:
            row = ET.fromstring(content)
            if int(row.get("PostTypeId")) == 1:
                words_score_dict = {}
                score = int(row.get("Score"))
                title = re.findall("\\w+", row.get("Title").lower())
                # make a dictionary for a row 
                for word in title:
                    if (word not in stop_words_dict):
                        words_score_dict[word] = score
                year = int(row.get("CreationDate").split('-', 1)[0])
                # add rows data to general years data
                if year not in year_scores_dict:
                    year_scores_dict[year] = words_score_dict
                else:
                    year_scores_dict[year] = merge_two_dicts(year_scores_dict[year], words_score_dict)
    return year_scores_dict


def make_stop_words_dict(stop_filepath: str):
    # create a dictionary of stopwords
    stop_words_dict = {}
    with open(stop_filepath, encoding = "koi8-r") as fin:
        stop_words = fin.readlines()
        for word in stop_words:
            stop_words_dict[word.rstrip()] = 1
    
    return stop_words_dict
    

def build_scorer_dict_from_xml(xml_filepath: str, stop_filepath: str):
    stop_words_dict = make_stop_words_dict(stop_filepath)
    year_scores_dict = make_year_scores_dict(xml_filepath, stop_words_dict)
    return year_scores_dict
            

def process_query(scorer_dict : dict, begin_year: int, end_year: int, top_n: int):
    logger.debug(
        'got query "%s,%s,%s"',  
        str(begin_year), str(end_year), str(top_n))

    total_dict = {}
    i = begin_year
    while (i <= end_year and len(total_dict) == 0):
        try:
            total_dict = scorer_dict[i]
            i = i + 1
        except:
            i = i + 1
    
    while i <= end_year:
        try:
            total_dict = merge_two_dicts(total_dict, scorer_dict[i])
            i = i + 1
        except:
            i = i + 1

    sorted_query = sorted(total_dict.items(), key=lambda x: (-x[1],x[0]))
    result = []
    result_size = top_n if top_n <= len(sorted_query) else len(sorted_query)
    if (top_n > len(sorted_query)):
        logger.warning(
            'not enough data to answer, found %s words out of %s for period "%s,%s"',
            str(result_size), str(top_n), str(begin_year), str(end_year))
        warn_logger.warning(
            'not enough data to answer, found %s words out of %s for period "%s,%s"',
            str(result_size), str(top_n), str(begin_year), str(end_year))
    
    for i in range(result_size):
        result.append(list(sorted_query[i]))
    
    result_for_json = {"start": begin_year, "end": end_year, "top": result}
    return json.dumps(result_for_json)


def callback_query(arguments):
    scorer_dict = build_scorer_dict_from_xml(arguments.questions, arguments.stopwords)
    logger.info("process XML dataset, ready to serve queries")
    with open(arguments.queries) as queries_fin:
        for query in queries_fin:
            query = query.rstrip("\n").split(",")
            top_words = process_query(scorer_dict, int(query[0]), int(query[1]), int(query[2]))
            print(top_words)
    logger.info("finish processing queries")


def setup_parser(parser):
    parser.add_argument(
        "--questions",
        dest="questions",
        help="path to retrieve questions database",
    )
    parser.add_argument(
        "--stop-words",
        dest="stopwords",
        help="path to load stopwords from",
    )
    parser.add_argument(
        "--queries",
        dest="queries",
        help="path to csv file of queries",
    )
    parser.set_defaults(callback=callback_query)


def setup_logging():
    with open(DEFAULT_LOGGING_CONFIG_PATH) as config_fin:
        logging.config.dictConfig(yaml.safe_load(config_fin))


def main():
    setup_logging()
    parser = ArgumentParser(
        prog = "stackoverflow-analytics",
        description = "tool to find most popular word upvotes in a given year periods",
    )
    setup_parser(parser)
    arguments = parser.parse_args()
    arguments.callback(arguments)


if __name__ == "__main__":
    main()