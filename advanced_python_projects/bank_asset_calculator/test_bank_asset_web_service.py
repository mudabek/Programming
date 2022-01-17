from bank_asset_web_service import (
    parse_cbr_currency_base_daily, 
    query_daily_rate,
    app,
    page_not_found,
    parse_cbr_key_indicators,
    query_key_indicators,
    get_assets_list,
    get_queried_assets,
    calculate_queried_revenue,
)
from flask import request
import pytest
import requests

TEST_EXCHANGE_RATES_HTML_TEXT = "test_exchange_rates_html_file.txt"
TEST_KEY_INDICATORS_HTML_TEXT = "test_key_indicators_html_file.txt"

@pytest.fixture
def client():
    with app.test_client() as client:
        yield client

def test_get_correct_404_message(client):
    app_response = client.get("/wrongurl")
    assert 404 == app_response.status_code
    assert "This route is not found" in app_response.data.decode(app_response.charset)

def test_parse_parse_cbr_currency_base_daily():
    with open(TEST_EXCHANGE_RATES_HTML_TEXT, 'rb') as f:
        text = f.read()
        daily_rates_dict = parse_cbr_currency_base_daily(text)
        assert daily_rates_dict['JPY'] == 72.9265 / 100.0
        assert daily_rates_dict['UZS'] == 72.0439 / 10000.0
        assert daily_rates_dict['AUD'] == 57.0229

def test_query_daily_rate(client):
    app_response = client.get("/cbr/daily")
    daily_rates_dict = app_response.get_json()
    assert daily_rates_dict['JPY'] is not None
    assert daily_rates_dict['UZS'] is not None
    assert daily_rates_dict['AUD'] is not None

def test_parse_cbr_key_indicators():
    with open(TEST_KEY_INDICATORS_HTML_TEXT, 'rb') as f:
        text = f.read()
        key_indicators_dict = parse_cbr_key_indicators(text)
        assert key_indicators_dict['EUR'] == 91.9822
        assert key_indicators_dict['USD'] == 75.4571
        assert key_indicators_dict['Au'] == 4529.59
        assert key_indicators_dict['Pd'] == 5667.14

def test_query_key_indicators(client):
    app_response = client.get("/cbr/key_indicators")
    key_indicators_dict = app_response.get_json()
    assert key_indicators_dict['EUR'] is not None
    assert key_indicators_dict['USD'] is not None
    assert key_indicators_dict['Au'] is not None
    assert key_indicators_dict['Pd'] is not None

def test_add_asset(client):
    app_response = client.get("/api/asset/add/USD/dollars/100/0.5")
    assert 200 == app_response.status_code
    assert "dollars" in app_response.data.decode(app_response.charset)
    app_response = client.get("/api/asset/add/EUR/euros/200/1.5")
    assert 200 == app_response.status_code
    assert "euros" in app_response.data.decode(app_response.charset)
    app_response = client.get("/api/asset/add/USD/dollars/120/0.5")
    assert 403 == app_response.status_code
    app_response = client.get("/api/asset/add/USD/euros/125/0.5")
    assert 403 == app_response.status_code

def test_clean_up_assets(client):
    app_response = client.get("/api/asset/cleanup")
    assert 200 == app_response.status_code

def test_get_assets_list(client):
    client.get("/api/asset/add/UZS/soum/200/1.5")
    client.get("/api/asset/add/USD/dollars/100/0.5")
    app_response = client.get("/api/asset/list")
    sorted_assets = app_response.get_json()
    expected_asset_list = [['USD', 'dollars', 100.0, 0.5], 
                           ['UZS', 'soum', 200.0, 1.5]]
    assert expected_asset_list == sorted_assets

def test_get_queried_assets(client):
    app_response = client.get("/api/asset/get?name=soum&name=dollars")
    queried_assets = app_response.get_json()
    expected_asset_list = [['USD', 'dollars', 100.0, 0.5], 
                           ['UZS', 'soum', 200.0, 1.5]]
    assert expected_asset_list == queried_assets

def test_calculate_queried_revenue(client):
    app_response = client.get("/api/asset/calculate_revenue?period=3&period=5")
    app_response.status_code == 200
