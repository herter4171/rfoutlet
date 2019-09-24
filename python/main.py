from flask import Flask
from data_table import get_table
from photo_parse import photo_parse

app = Flask(__name__)

@app.route('/')
def index():
    # Print heading and sensor data
    html_str = "<h1>Plant Status</h1>"
    html_str += "<h2>Sensor Data</h2>"

    try:
        html_str += get_table()
    except:
        html_str += "Data not present.  Is the program running on the Raspberry Pi?"

    try:
        # Show latest plant photo
        html_str += "<h2>Latest Photo</h2>"

        pp = photo_parse()
        img_path = pp.get_latest_path()
        print(img_path)

        # Add image tag to HTML
        html_str += "<img src=\"/{}\" width=\"500\"/>".format(img_path)
        import os
        print(os.getcwd())
    except:
        html_str += "Image not present.  Has one been uploaded?"

    return html_str

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
