from selenium import webdriver

url = "https://iss-sim.spacex.com/"
file_path = "sim_data.csv"

driver = webdriver.Chrome()
driver.get(url)

# roll_val, roll_velocity, pitch_val, pitch_velocity, yaw_val, yaw_velocity, x_val, y_val, z_val, x_velocity, y_velocity, z_velocity, range_val, rate = "", "", "", "", "", "", "", "", "", "", "", "", "", ""

# the current live data
val_dict_current = {
    "roll_val": "",
    "roll_velocity": "",

    "pitch_val": "",
    "pitch_velocity": "",

    "yaw_val": "",
    "yaw_velocity": "",

    "x_val": "",
    "y_val": "",
    "z_val": "",
    
    "range_val": "",
    "rate": ""
}

# the xpath locations of all the data
xpath_dict = { 
    "roll_val": "(//div[@class='error'])[2]",
    "roll_velocity": "(//div[@id='roll']//div)[2]",

    "pitch_val": "//div[@class='error']",
    "pitch_velocity": "(//div[@class='hud-item']//div)[2]",

    "yaw_val": "(//div[@class='error'])[3]",
    "yaw_velocity": "(//div[@id='yaw']//div)[2]",

    "x_val": "//div[@id='x-range']//div[1]",
    "y_val": "//div[@id='y-range']//div[1]",
    "z_val": "//div[@id='z-range']//div[1]",

    "range_val": "(//div[@id='range']//div)[2]",
    "rate": "(//div[@id='rate']//div)[2]"
}

while (1):

    # where the data will be stored before writing
    file_buffer = ""

    # collects the data
    val_dict_current["roll_val"] = driver.find_element_by_xpath(xpath_dict["roll_val"]).text
    val_dict_current["roll_velocity"] = driver.find_element_by_xpath(xpath_dict["roll_velocity"]).text

    val_dict_current["pitch_val"] = driver.find_element_by_xpath(xpath_dict["pitch_val"]).text
    val_dict_current["pitch_velocity"] = driver.find_element_by_xpath(xpath_dict["pitch_velocity"]).text

    val_dict_current["yaw_val"] = driver.find_element_by_xpath(xpath_dict["yaw_val"]).text
    val_dict_current["yaw_velocity"] = driver.find_element_by_xpath(xpath_dict["yaw_velocity"]).text

    val_dict_current["x_val"] = driver.find_element_by_xpath(xpath_dict["x_val"]).text
    val_dict_current["y_val"] = driver.find_element_by_xpath(xpath_dict["y_val"]).text
    val_dict_current["z_val"] = driver.find_element_by_xpath(xpath_dict["z_val"]).text

    val_dict_current["range_val"] = driver.find_element_by_xpath(xpath_dict["range_val"]).text
    val_dict_current["rate"] = driver.find_element_by_xpath(xpath_dict["rate"]).text

    # reformats the data
    val_dict_current["roll_val"] = val_dict_current["roll_val"].replace("°", "")
    val_dict_current["pitch_val"] = val_dict_current["pitch_val"].replace("°", "")
    val_dict_current["yaw_val"] = val_dict_current["yaw_val"].replace("°", "")
    
    val_dict_current["roll_velocity"] = val_dict_current["roll_velocity"].replace("°/s", "")
    val_dict_current["pitch_velocity"] = val_dict_current["pitch_velocity"].replace("°/s", "")
    val_dict_current["yaw_velocity"] = val_dict_current["yaw_velocity"].replace("°/s", "")

    val_dict_current["x_val"] = val_dict_current["x_val"].replace(" m", "")
    val_dict_current["y_val"] = val_dict_current["y_val"].replace(" m", "")
    val_dict_current["z_val"] = val_dict_current["z_val"].replace(" m", "")

    val_dict_current["range_val"] = val_dict_current["range_val"].replace(" m", "")
    val_dict_current["rate"] = val_dict_current["rate"].replace("m/s", "")

    file_buffer += (val_dict_current["roll_val"] + "\n" + val_dict_current["roll_velocity"] + "\n" + val_dict_current["pitch_val"] + "\n" + val_dict_current["pitch_velocity"] + "\n" + val_dict_current["yaw_val"] + "\n" + val_dict_current["yaw_velocity"] + "\n" + val_dict_current["x_val"] + "\n" + val_dict_current["y_val"] + "\n" + val_dict_current["z_val"] + "\n" + val_dict_current["rate"])

    with open(file_path, 'w') as file:
        file.write(file_buffer)

    # print statements to read data from software

    #print(val_dict_current["roll_val"]) # verified
    #print(val_dict_current["pitch_val"]) # verified
    #print(val_dict_current["yaw_val"]) # verified

    # print(val_dict_current["roll_velocity"]) # verified
    # print(val_dict_current["pitch_velocity"]) # verified
    # print(val_dict_current["yaw_velocity"]) # verified

    # print(val_dict_current["x_val"]) # verified
    # print(val_dict_current["y_val"]) # verified
    #print(val_dict_current["z_val"]) # verified

    # print(val_dict_current["range_val"])
    # print(val_dict_current["rate"])

    