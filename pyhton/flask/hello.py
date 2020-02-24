from flask import Flask
app = Flask(__name__)
app.config['SERVER_NAME'] = 'foocay.com:8080'
@app.route("/")
def index():
    return "hello World!"
