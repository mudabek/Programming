from argparse import (ArgumentParser, ArgumentDefaultsHelpFormatter, 
                      FileType, ArgumentTypeError)
from collections import defaultdict
import struct
import pdb
import sys
import unicodedata
from io import TextIOWrapper

DEFAULT_DATASET_PATH = "wikipedia_sample.txt"
DEFAULT_OUTPUT_PATH = "default_inverted"


class EncodedFileType(FileType):
    def  __call__(self, string):
        if string == '-':
            if 'r' in self._mode:
                stdin = TextIOWrapper(sys.stdin.buffer, encoding = self._encoding)
                return stdin
            elif 'm' in self._mode:
                stdout = TextIOWrapper(sys.stdout.buffer, encoding = self._encoding)
                return stdout
            else:
                msg = 'argument "-" with mode %r' % self._mode
                raise ValueError(msg)

        try:
            return open(string, self._mode, self._bufsize, self._encoding,
                        self._errors)
        except OSError as e:
            message = "can't open '%s' : %s"
            raise ArgumentTypeError(message % (string, e))

class InvertedIndex:
    def __init__(self, table = {}):
        self.table = table

    def query(self, words: list):
        temp = []
        result = self.table[words[0]]
        for word in words:
            temp = self.table[word]
            result = list(set(result) & set(temp))
        result.sort()
        return result
     
    def dump(self, filepath: str):
        fout = open(filepath, 'wb')
        # pack dictionary length
        data_len = len(self.table)
        data = struct.pack('>i', data_len)
        fout.write(data)
        for key in self.table:
            # pack string key 
            key_str = key.encode('utf-8')
            str_len = len(key_str)
            data = struct.pack('>B', str_len)
            fout.write(data)
            data = struct.pack('>' + str(str_len) + 's', key_str)
            fout.write(data)
            # pack integer values
            id_cnt = len(self.table[key])
            data = struct.pack('>H', id_cnt)
            fout.write(data)
            for doc_id in self.table[key]:
                data = struct.pack('>H', doc_id)
                fout.write(data)
        fout.close()

    @classmethod
    def load(cls, filepath: str):
        fin = open(filepath, 'rb')
        # unpack dictionary size
        data = fin.read(4)
        count = struct.unpack('>i', data)[0]
        words_ids = defaultdict(set)

        i = 0
        while i < count:
            # unpack string key
            raw_len = fin.read(1)
            str_len = struct.unpack('>B', raw_len)[0]
            str_code = '>' + str(str_len) + 's'
            raw_str = fin.read(str_len)
            str_enc = struct.unpack(str_code, raw_str)[0]
            key = str_enc.decode('utf-8')
            # unpack ids for each key
            data = fin.read(2)
            id_cnt = struct.unpack('>H', data)[0]
            j = 0
            words_ids[key] = set()
            while j < id_cnt:
                data = fin.read(2)
                value = struct.unpack('>H', data)[0]
                words_ids[key].add(value)
                j = j + 1
            i = i + 1
        fin.close()
        return cls(words_ids)

    def __eq__(self, other):
        return self.table == other.table

def load_documents(filepath: str):
    text_map = {}
    with open(filepath, encoding = 'UTF-8') as fin:
        for l in fin:
            l = l.strip("\n")
            if l:
                doc_id, text = l.split("\t", 1)
                text_map[doc_id] = text
    return text_map

def build_inverted_index(documents):
    words_ids = defaultdict(set)
    for doc_id, text in documents.items():
        words = text.split()
        for word in words:
            words_ids[word].add(int(doc_id))
    return InvertedIndex(words_ids)

def callback_build(arguments):
    doc = load_documents(arguments.dataset)
    inv_index = build_inverted_index(doc)
    inv_index.dump(arguments.output)

def callback_query_helper(query, inv_index):
    doc_ids = inv_index.query(query)
    print(','.join(str(cur_id) for cur_id in doc_ids))

def callback_query(arguments):
    inv_index = InvertedIndex.load(arguments.index_path)
    if arguments.queries is not None:
        for query in arguments.queries:
            callback_query_helper(query, inv_index)      
    else:
        for query in arguments.query_file:
            clean_query = query.rstrip("\n").split()
            callback_query_helper(clean_query, inv_index)


def setup_parser(parser):
    subparsers = parser.add_subparsers(help = "choose command")

    build_parser = subparsers.add_parser(
        "build", help = "build inverted index and save it to file",
        formatter_class=ArgumentDefaultsHelpFormatter,
    )
    build_parser.add_argument(
        "-d", "--dataset", dest = "dataset",
        default = DEFAULT_DATASET_PATH,
        help = "path to dataset to load",
    )
    build_parser.add_argument(
        "-o", "--output", dest = "output",
        default = DEFAULT_OUTPUT_PATH,
        help = "path where to save inverted index",
    )
    build_parser.set_defaults(callback = callback_build)

    query_parser = subparsers.add_parser(
        "query", help = "query inverted index",
        formatter_class=ArgumentDefaultsHelpFormatter,
    )
    query_parser.add_argument(
        "-i", "--index", required = True, dest = "index_path",
        help = "path to inverted index",
    )
    query_file_group = query_parser.add_mutually_exclusive_group(required = True)
    query_file_group.add_argument(
        "-q", "--query", required = False, action = "append", nargs = "+",
        help = "query for finding documents with keywords provided",
        dest = "queries"
    )
    query_file_group.add_argument(
        "--query-file-cp1251", 
        type = EncodedFileType("r", encoding="cp1251"),
        default=TextIOWrapper(sys.stdin.buffer, encoding="cp1251"), dest = "query_file", 
        help = "list of queries in cp1251 formatted document",
    )
    query_file_group.add_argument(
        "--query-file-utf8",
        type = EncodedFileType("r", encoding="utf-8"),
        default=sys.stdin, dest = "query_file",
        help = "list of queries in utf8 formatted document",
    )
    query_parser.set_defaults(
        dataset = DEFAULT_DATASET_PATH,
        callback = callback_query,
    )

def process_arguments(dataset_filepath: str, query: list):
    documents = load_documents(dataset_filepath)
    inverted_index = build_inverted_index(documents)
    document_ids = inverted_index.query(query)
    return document_ids

def main():
    parser = ArgumentParser(
        prog = "inverted-index",
        description = "tool to build, dump, load and query inverted index",
    )
    setup_parser(parser)
    arguments = parser.parse_args()
    arguments.callback(arguments)

if __name__ == "__main__":
    main()