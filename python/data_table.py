from flask_table import Table, Col
import redis
from datetime import datetime
from pytz import timezone

class data_table(Table):
    l_align = {'align': 'left'}
    r_align = {'align': 'right'}

    item = Col('Item',
               th_html_attrs=l_align,
               td_html_attrs=l_align)

    value = Col('Value',
                th_html_attrs=r_align,
                td_html_attrs=r_align)

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
    table.border = True

    time_stamp = "<b>Note:</b> Updated at "
    time_stamp += get_last_write(r)
    time_stamp = time_stamp[:time_stamp.rfind(':')]
    time_stamp += " PST" + "<br>"*2

    return time_stamp + table.__html__()

def get_last_write(redis_conn):
    assert(isinstance(redis_conn, redis.Redis))
    epoch_time = int(redis_conn.get('Last_Write'))
    utc_time = datetime.fromtimestamp(epoch_time, tz=timezone('UTC'))
    local_time = utc_time.astimezone(tz=timezone('US/Pacific'))

    return str(local_time)


