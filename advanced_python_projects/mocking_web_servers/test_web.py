from argparse import Namespace
from getpass import getpass
from unittest.mock import patch, MagicMock
import json
from json import JSONDecodeError
from contextlib import nullcontext as do_not_raise_exception
from requests import exceptions

import requests
import pytest
import pdb

DEFAULT_STATUS_CODE = 200
DEFAULT_ENCODING = "utf-8"
GITHUB_API_RESPONSE_FILEPATH = "github_api_response.txt"
GITHUB_DOCS_RESPONSE_FILEPATH = "github_docs_response.html"
URL_GITHUB_API = "https://api.github.com"
URL_GITHUB_DOCS = "https://docs.github.com"
URL_AUTH_TEST = "https://jigsaw.w3.org/HTTP/Basic/"
URL_UNKNOWN = "https://not-existing-url.com"

"""
if we want to use feature of skipping integration_test
and slow_test then we need to modify conftest.py
check video W6L104
"""

def build_response_mock_from_content(content, encoding=DEFAULT_ENCODING, status_code=DEFAULT_STATUS_CODE):
    text = content.decode(encoding)
    response = MagicMock(
        text=text, 
        content=content, 
        encoding=encoding, 
        status_code = status_code,
        json = json.loads(text),
    )
    response.json.side_effect=lambda: json.loads(text)
    return response

@patch("requests.get")
@pytest.mark.parametrize(
    "target_url, expectation",
    [
        (URL_GITHUB_API, do_not_raise_exception),
        (URL_GITHUB_DOCS, pytest.raises(JSONDecodeError)),
        (URL_UNKNOWN, pytest.raises(exceptions.ConnectionError)),
    ]
)
def test_we_can_mock_web(mock_requests_get, target_url, expectation):
    mock_requests_get.side_effect = callback_requests_get
   
    with expectation:
        response = requests.get(target_url)
        assert isinstance(response.json(), dict)
        assert response.status_code == 200
        assert "github" in response.text

def callback_requests_get(url):
    url_mapping = {
        URL_GITHUB_API: GITHUB_API_RESPONSE_FILEPATH,
        URL_GITHUB_DOCS: GITHUB_DOCS_RESPONSE_FILEPATH,
    }
    if url in url_mapping:
        mock_content_filepath = url_mapping[url]
        with open(mock_content_filepath, "rb") as content_fin:
            content = content_fin.read()
        mock_response = build_response_mock_from_content(content=content)
        return mock_response

    raise exceptions.ConnectionError(f"exceeded max trial connection to {url}")
        
#@pytest.mark.integration_test
@pytest.mark.parametrize(
    "target_url, expected_outcome",
    [
        (URL_GITHUB_API, True),
        (URL_AUTH_TEST, False),
    ]
)

#@pytest.mark.integration_test
def test_http_api_request_is_successful(target_url, expected_outcome):
    response = requests.get(target_url)
    assert expected_outcome == bool(response)

#@pytest.mark.integration_test
def test_auth_website_requires_correct_credentials():
    response = requests.get(URL_AUTH_TEST, auth=("user", "wrong_pasword"))
    assert 400 <= response.status_code < 500

#@pytest.mark.integration_test
@patch("test_web.getpass")
def test_auth_website_accept_correct_credentials(mock_getpass):
    mock_getpass.return_value = "guest"
    response = requests.get(URL_AUTH_TEST, auth=("guest", getpass()))
    assert True == bool(response.status_code)