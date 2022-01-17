import pytest
from web_hello_world import (
    app as hello_world_app, 
    DEFAULT_GREETING_COUNT, 
    MAX_GREETING_COUNT,
    TOO_MANY_GREETINGS,
)


@pytest.fixture
def client():
    with hello_world_app.test_client() as client:
        yield client

def test_service_reply_to_root_path(client):
    response = client.get("/")
    assert "world" in response.data.decode(response.charset)

def test_service_reply_to_username(client):
    response = client.get("/hello/Vasya")
    assert "Vasya" in response.data.decode(response.charset)

def test_service_reply_to_username_with_default_num(client, num=DEFAULT_GREETING_COUNT):
    username = "Vasya"
    response = client.get(f"/hello/{username}", follow_redirects=True)
    response_text =  response.data.decode(response.charset)
    greeting_count = response_text.count(username)
    assert DEFAULT_GREETING_COUNT == greeting_count

def test_service_reply_to_username_several_times(client):
    username = "Petya"
    expected_greeting_count = 15
    response = client.get(f"/hello/{username}/{expected_greeting_count}")
    response_text =  response.data.decode(response.charset)
    greeting_count = response_text.count(username)
    assert expected_greeting_count == greeting_count

def test_service_reply_to_escaped_username(client):
    non_escaped_tag = "<br>"
    username = "Petya"
    expected_greeting_count = 15
    response = client.get(f"/hello/{non_escaped_tag}{username}/{expected_greeting_count}")
    response_text =  response.data.decode(response.charset)
    greeting_count = response_text.count(username)
    assert expected_greeting_count == greeting_count
    assert 0 == response_text.count(non_escaped_tag)

def test_service_hello_to_username_with_slash(client):
    username = "Vasya"
    response = client.get(f"/hello/{username}/")
    assert 200 == response.status_code

def test_service_reply_to_overflow_count(client):
    username = "Petya"
    given_greeting_count = MAX_GREETING_COUNT + 1
    expected_greeting_count = DEFAULT_GREETING_COUNT
    response = client.get(f"/hello/{username}/{given_greeting_count}", follow_redirects=True)
    response_text =  response.data.decode(response.charset)
    greeting_count = response_text.count(username)
    assert expected_greeting_count == greeting_count

def test_service_reply_to_many_num(client):
    username = "Petya"
    given_greeting_count = TOO_MANY_GREETINGS
    response = client.get(f"/hello/{username}/{given_greeting_count}", follow_redirects=True)
    assert 404 == response.status_code
    response_text =  response.data.decode(response.charset)
    greeting_count = response_text.count(username)
    assert 0 == greeting_count
