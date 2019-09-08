from selenium import webdriver
import time

browser = webdriver.Chrome()
browser.get('http://192.168.1.1')

elem_user = browser.find_element_by_id('login_username')
elem_pw = browser.find_element_by_id('login_password')
elem_btn = browser.find_element_by_tag_name('button')

elem_user.send_keys('useradmin')
elem_pw.send_keys('pd6sd')
elem_btn.click()
time.sleep(10)

browser.close()
browser.quit()
