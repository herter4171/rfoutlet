import os
from datetime import datetime

class photo_parse(object):

    __ext__ = ".jpg" # Image file extension


    def __init__(self, image_dir = "static"):
        """Instantiate with static image directory from Docker Compose"""
        self.__image_dir__ = image_dir

    def get_latest_path(self):
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
