from flask_table import Table, Col
import redis
from util import utc_epoch_to_timestamp

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
    time_stamp += "<br>"*2

    return time_stamp + table.__html__()

def get_last_write(redis_conn):
    """Returns a time stamp for when data was last written"""
    assert(isinstance(redis_conn, redis.Redis))
    epoch_time = int(redis_conn.get('Last_Write'))

    return utc_epoch_to_timestamp(epoch_time)


