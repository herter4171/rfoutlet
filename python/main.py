from flask import Flask
import redis

app = Flask(__name__)

@app.route('/')
def index():
    return get_foo()

def get_foo():
    r = redis.Redis(host='redis', port=6379, db=0)
    return r.get('foo')

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')