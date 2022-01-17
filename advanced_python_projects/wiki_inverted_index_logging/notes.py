"""
simple_formatter = logging.Formatter(
    fmt = "%(asctime)s %(levelname)s %(message)s",
    datefmt = "%Y-%m-%d-%H:%M:%S",
)
file_handler = logging.FileHandler(
    filename = "inverted_index.log",
)
#below works in a way like filters for logging messages we want to see
file_handler.setLevel(logging.DEBUG)
file_handler.setFormatter(simple_formatter)

logger = logging.getLogger(APPLICATION_NAME)
logger.setLevel(logging.DEBUG)
logger.addHandler(file_handler)

#default handler
logger = logging.getLogger()
logger.addHandler(file_handler)
"""


#logger = logging.getLogger(__name__)
"""
logging.basicConfig(
    filename = "inverted_index.log",
    format = "%(asctime)s %(levelname)s %(message)s",
    datefmt = "%Y-%m-%d-%H:%M:%S", 
    level=logging.DEBUG,
)
yaml-multiline.info -> play around with yaml interpreter
check PyYaml
"""


python howto has many things
howto logging
howto logging.config
howto logging-cookbook


###############################
MOCK
###############################


