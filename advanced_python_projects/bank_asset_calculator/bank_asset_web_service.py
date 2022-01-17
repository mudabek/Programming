from flask import Flask, request, abort, jsonify
from lxml import etree
import requests

app = Flask(__name__)
app.bank = []
app.asset_names = {}
CBR_DAILY_RATES_URL = "https://www.cbr.ru/eng/currency_base/daily/"
CBR_KEY_INDICATORS_URL = "https://www.cbr.ru/eng/key-indicators/"

@app.errorhandler(404)
def page_not_found(error):
    return 'This route is not found', 404

@app.errorhandler(503)
def page_not_available(error):
    return 'CBR service is unavailable', 503

@app.route("/cbr/daily")
def query_daily_rate():
    return jsonify(parse_cbr_currency_base_daily(get_daily_rate_page()))

def get_daily_rate_page():
    try:
        cbr_daily_response = requests.get(CBR_DAILY_RATES_URL)
        if not cbr_daily_response.ok:
            abort(503)
        return cbr_daily_response.text
    except:
        abort(503)   

def parse_cbr_currency_base_daily(daily_rate_text):
    daily_rate_dict = {}
    root = etree.fromstring(daily_rate_text, etree.HTMLParser())
    raw_table_data = root.xpath("//table[@class='data']")[0].getchildren()[0].getchildren()[1:]
    for currency_data in raw_table_data:
        cur_char_code = currency_data[1].text
        cur_rate = float(currency_data[4].text) / float(currency_data[2].text)
        daily_rate_dict[cur_char_code] = cur_rate
    return daily_rate_dict

@app.route("/cbr/key_indicators")
def query_key_indicators():
    return jsonify(parse_cbr_key_indicators(get_key_indicators_page()))

def get_key_indicators_page():
    try:
        cbr_key_indicators_response = requests.get(CBR_KEY_INDICATORS_URL)
        if not cbr_key_indicators_response.ok:
            abort(503)
        return cbr_key_indicators_response.text
    except:
        abort(503)
    

def parse_cbr_key_indicators(key_indicators_text):
    key_indicators_dict = {}
    root = etree.fromstring(key_indicators_text, etree.HTMLParser())
    raw_key_indicators_data = root.xpath("//div[@class='table key-indicator_table']")
    foreign_currency_data = raw_key_indicators_data[0]
    precious_metals_data = raw_key_indicators_data[1]
    parse_key_indicators_table(foreign_currency_data, key_indicators_dict)
    parse_key_indicators_table(precious_metals_data, key_indicators_dict)
    return key_indicators_dict

def parse_key_indicators_table(table_data, key_indicators_dict):
    trs = table_data.getchildren()[0].getchildren()[0].getchildren()[1:]
    for key_indicator_group in trs:
        char_code = key_indicator_group.getchildren()[0].getchildren()[0].getchildren()[-1].text
        value = float(key_indicator_group.getchildren()[-1].text.replace(',', ''))
        key_indicators_dict[char_code] = value

@app.route("/api/asset/add/<char_code>/<name>/<capital>/<interest>")
def add_asset(char_code, name, capital, interest):
    new_asset = Asset(char_code, name, float(capital), float(interest))
    if name not in app.asset_names:
        app.bank.append(new_asset)
        app.asset_names[name] = 1
        return f'Asset {name} was successfully added', 200
    else:
        abort(403)

@app.route("/api/asset/list")
def get_assets_list():
    asset_list = []
    for asset in app.bank:
        asset_list.append(asset.asset_as_list())
    return jsonify(Sort(asset_list))

def Sort(sub_list):
    sub_list.sort(key = lambda x: x[0]) 
    return sub_list 
    
@app.route("/api/asset/cleanup")
def clean_up_assets():
    app.bank = []
    app.asset_names = {}
    return "Assets collection cleaned", 200

@app.route("/api/asset/get")
def get_queried_assets():
    user_query = request.args.getlist("name")
    query_result = []   
    for cur_asset_name in user_query:
        for asset in app.bank:
            if cur_asset_name == asset.name:
                query_result.append(asset.asset_as_list())    
    return jsonify(Sort(query_result))

@app.route("/api/asset/calculate_revenue")
def calculate_queried_revenue():
    queried_periods = request.args.getlist("period")
    daily_rates_dict = parse_cbr_currency_base_daily(get_daily_rate_page())
    key_indicators_dict = parse_cbr_key_indicators(get_key_indicators_page())
    revenues_dict = {}
    for period in queried_periods:
        total_revenue = 0
        for asset in app.bank:
            if asset.char_code in key_indicators_dict:
                exchange_rate = key_indicators_dict[asset.char_code]
            else:
                exchange_rate = daily_rates_dict[asset.char_code]
            total_revenue = total_revenue + asset.calculate_revenue(int(period), exchange_rate)
        revenues_dict[int(period)] = round(total_revenue, 7)
    return jsonify(revenues_dict)

class Asset:
    def __init__(self, char_code: str, name: str, capital: float, interest: float):
        self.char_code = char_code
        self.name = name
        self.capital = capital
        self.interest = interest

    def calculate_revenue(self, years: int, exchange_rate: float) -> float:
        revenue = self.capital * ((1.0 + self.interest) ** years - 1.0) * exchange_rate
        return revenue

    @classmethod
    def build_from_str(cls, raw: str):
        char_code, name, capital, interest = raw.strip().split()
        capital = float(capital)
        interest = float(interest)
        asset = cls(char_code=char_code, name=name, capital=capital, interest=interest)
        return asset
    
    def asset_as_list(self):
        return [self.char_code, self.name, self.capital, self.interest]

    def __repr__(self):
        repr_ = f"{self.__class__.__name__}({self.char_code}, {self.name}, {self.capital}, {self.interest})"
        return repr_