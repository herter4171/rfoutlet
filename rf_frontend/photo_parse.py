import os
from datetime import datetime
from util import utc_epoch_to_timestamp


class photo_parse(object):

    __ext__ = ".jpg" # Image file extension

    @property
    def latest_path(self):
        """Parses timestamp to keys mapped to paths to return latest date path"""
        image_dict = {}

        for file in os.listdir(self.__image_dir__):
            if file.endswith(photo_parse.__ext__):
                # Parse image full path
                full_path = os.path.join(self.__image_dir__, file)

                # Extract date from filename, and add to dict
                date = datetime.strptime(file, '%Y-%b-%d' + photo_parse.__ext__)
                image_dict[date] = full_path

        # Return path to most recent picture
        return image_dict[max(image_dict)]

    def __init__(self, image_dir = "static"):
        """Instantiate with static image directory from Docker Compose"""
        self.__image_dir__ = image_dir


    def get_image_html(self, width = 500):
        img_html = "<b>Note:</b> Updated at "
        img_path = self.latest_path

        # Get readable time stamp from image file
        epoch_time = os.path.getmtime(img_path)
        img_html += utc_epoch_to_timestamp(epoch_time) + "<br>"*2

        # Append image tag
        img_html += "<img src=\"/{}\" width=\"{}\"/>".format(img_path, str(width))
        return img_html

