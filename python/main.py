from flask import Flask
from data_table import get_table

app = Flask(__name__)

@app.route('/')
def index():
    # Print heading and sensor data
    html_str = "<h1>Plant Status</h1>"
    html_str += "<h2>Sensor Data</h2>"
    html_str += get_table()

    # Show latest plant photo
    html_str += "<h2>Latest Photo</h2>"

    return html_str

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
