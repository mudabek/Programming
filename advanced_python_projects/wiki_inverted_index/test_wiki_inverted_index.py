from wiki_inverted_index import (load_documents, InvertedIndex, 
        build_inverted_index, callback_query)
from argparse import Namespace

SIMPLE_TEST_FILE = "test_simple.txt"
SIMPLER_TEST_FILE = "inv_test.txt"
TINY_WIKIPEDIA_FILE = "wikipedia_sample_tiny"
INV_INDEX_FOR_QUERY_TEST = "query_tester.txt"
QUERIES_FILE = "query_test.txt"


def test_load_do_loads_properly():
    test_text = {'1':     "hello world it's me here", 
                 '2' :    "the world is mine",
                 '3' :    "and nothing can mend me",
                 '4' :    "mine is not to to mine world"}
    file_text = load_documents(SIMPLE_TEST_FILE)
    assert test_text == file_text, (
        "test text and file text are not the same"
    )

def test_inverted_index_constructor():
    InvertedIndex({1: "hello"})

def test_build_inverted_index_do_work():
    test_dict = {"hello" : {1, 2}, "here" : {1, 3}, "there" : {2, 3}}
    inv_index = build_inverted_index(load_documents(SIMPLER_TEST_FILE))
    assert test_dict == inv_index.table, (
        "dictionary stored in inverted index is wrong"
    )

def test_query_do_work_correctly():
    query = ["world", "mine"]
    expected = [2, 4]
    inv_index = build_inverted_index(load_documents(SIMPLE_TEST_FILE))
    result = inv_index.query(query)
    assert expected == result, (
        "query not returning correct list of articles"
    )

def test_dump_and_load_do_work(tmpdir):
    temp = 'temp'
    docs = load_documents(TINY_WIKIPEDIA_FILE)
    inv_index = build_inverted_index(docs)
    inv_index.dump(temp)
    loaded_inv_index = InvertedIndex.load(temp)
    assert inv_index == loaded_inv_index, (
        "dump or load are not working correctly"
    )

def test_callback_query_do_process_queries_from_file(capsys):
    inv_index = build_inverted_index(load_documents(SIMPLE_TEST_FILE))
    inv_index.dump(INV_INDEX_FOR_QUERY_TEST)
    queries_fin = open(QUERIES_FILE, 'r')
    query_args = Namespace(
        index_path = INV_INDEX_FOR_QUERY_TEST,
        query_file = queries_fin,
        queries = None,
    )
    callback_query(query_args)
    captured = capsys.readouterr()
    assert "1" in captured.out
    assert "2,4" in captured.out, (
        "problem with callback query"
    )
    queries_fin.close()
    

def test_callback_query_do_process_queries_from_commandline_input(capsys):
    inv_index = build_inverted_index(load_documents(SIMPLE_TEST_FILE))
    inv_index.dump(INV_INDEX_FOR_QUERY_TEST)
    query_args = Namespace(
        index_path = INV_INDEX_FOR_QUERY_TEST,
        query_file = None,
        queries = [['hello'], ['world']],
    )
    callback_query(query_args)
    captured = capsys.readouterr()
    assert "1" in captured.out
    assert "2,4" in captured.out, (
        "problem with callback query"
    )