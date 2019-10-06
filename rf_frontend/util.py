from datetime import datetime
from pytz import timezone

def utc_epoch_to_timestamp(epoch_time, local_zone='US/Pacific'):
    """Converts a UNIX time stamp to a time stamp for US/Pacific"""
    utc_time = datetime.fromtimestamp(epoch_time, tz=timezone('UTC'))
    local_time = str(utc_time.astimezone(tz=timezone(local_zone)))

    # Remove the seconds trailing, and append time zone PST
    local_time = local_time[:local_time.rfind(':')]
    return ' '.join([local_time, local_zone])
