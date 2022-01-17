from stackoverflow_popularity_analytics import (
    make_stop_words_dict, merge_two_dicts,
    make_year_scores_dict, build_scorer_dict_from_xml,
    process_query, callback_query)
from argparse import Namespace

TEST_PATH = "xml_posts_test.xml"
TEST_STOP_WORDS_PATH = "stop_words_en.txt"
TEST_QUERIES_PATH = "queries_test.csv"


# 1) data 2008, score 38, "python or java or chill and drill"
# 4) data 2007, score -3, "hello world java here"
# 6) data 2008, score 2, "python is real"

def test_make_stop_words_dict():
    stop_words_dict = make_stop_words_dict(TEST_STOP_WORDS_PATH)
    assert stop_words_dict['and'] == 1
    assert stop_words_dict['is'] == 1
    assert stop_words_dict['me'] == 1

def test_merge_two_dicts_works():
    d1 = {'a' : 2, 'b' : 0, 'c' : -1}
    d2 = {'a' : 1, 'b' : -1, 'c' : 2}
    d_tot = {'a' : 3, 'b' : -1, 'c' : 1}
    assert d_tot == merge_two_dicts(d1, d2), (
        "dictionaries are not being merged correctly"
    )

def test_make_year_scores_dict():
    stop_words_dict = make_stop_words_dict(TEST_STOP_WORDS_PATH)
    year_scores_dict = make_year_scores_dict(TEST_PATH, stop_words_dict)
    assert year_scores_dict[2008]['python'] == 40
    assert year_scores_dict[2008]['java'] == 38
    assert year_scores_dict[2007]['java'] == -3

def test_build_scorer_from_xml():
    year_scores_dict = build_scorer_dict_from_xml(TEST_PATH, TEST_STOP_WORDS_PATH)
    assert year_scores_dict[2008]['python'] == 40
    assert year_scores_dict[2008]['java'] == 38
    assert year_scores_dict[2007]['java'] == -3

def test_process_query():
    scores_dict = build_scorer_dict_from_xml(TEST_PATH, TEST_STOP_WORDS_PATH)
    json_query1 = process_query(scores_dict, 2005, 2012, 2)
    json_query2 = process_query(scores_dict, 2021, 2022, 2)
    json_query3 = process_query(scores_dict, 2000, 2022, 0)
    assert json_query1 == '{"start": 2005, "end": 2012, "top": [["python", 40], ["chill", 38]]}'
    assert json_query2 == '{"start": 2021, "end": 2022, "top": []}'
    assert json_query3 == '{"start": 2000, "end": 2022, "top": []}'

def test_callback_query_works(capsys):
    query_args = Namespace(
        questions = TEST_PATH,
        stopwords = TEST_STOP_WORDS_PATH,
        queries = TEST_QUERIES_PATH,
    )
    callback_query(query_args)
    captured = capsys.readouterr()
    assert '{"start": 2007, "end": 2008, "top": [["python", 40], ["chill", 38]]}' in captured.out, (
        "problem with callback query"
    )

def test_data_teams_process_query():
    scores_dict = build_scorer_dict_from_xml(TEST_PATH, TEST_STOP_WORDS_PATH)
    json_query1 = process_query(scores_dict, 2019, 2019, 2)
    json_query2 = process_query(scores_dict, 2019, 2020, 4)
    assert json_query1 == '{"start": 2019, "end": 2019, "top": [["seo", 15], ["better", 10]]}'
    assert json_query2 == '{"start": 2019, "end": 2020, "top": [["better", 30], ["javascript", 20], ["python", 20], ["seo", 15]]}'
