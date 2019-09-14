from flask_table import Table, Col
import redis

class data_table(Table):
    item = Col('Item')
    value = Col('Value')

class data_item(object):
    def __init__(self, item, value):
        self.item = item
        self.value = value

    #const str_vec levelKeys = {};

    #// Used for get/set monitoring statuses
    #const str_vec statusKeys = {"Light_Status",
    #                            "Moist_Status",
    #                            "Resrv_Status"};
def get_table():
    r = redis.Redis(host='redis', port=6379, db=0)
    keys = ["Light_Level", "Moist_Level", "Resrv_Level",
            "Light_Status", "Moist_Status", "Resrv_Status"]

    items = []
    for key in keys:
        val = r.get(key).decode("utf-8")
        item = data_item(key.replace('_', ' '), val)
        items.append(item)

    table = data_table(items)

    return table.__html__()

