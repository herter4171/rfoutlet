from flask import Flask
from data_table import get_table

app = Flask(__name__)

@app.route('/')
def index():
    return get_table()

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')