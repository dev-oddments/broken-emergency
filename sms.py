from sdk.api.message import Message
from sdk.exceptions import CoolsmsException

# set api key, api secret
api_key = "NCSZXZP2KF8ACG//"
api_secret = "P5YVT2PREVK5SDVEPZ2L8YASH2KY9C//"

## 4 params(to, from, type, text) are mandatory. must be filled
params = dict()
params['type'] = 'sms' # Message type ( sms, lms, mms, ata )
params['to'] = '01066541533' # Recipients Number '01000000000,01000000001'
params['from'] = '01066541533' # Sender number
params['text'] = '자녀의 헬멧에 충격이 감지되었습니다.' # Message

cool = Message(api_key, api_secret)
try:
    response = cool.send(params)
    print("Success Count : %s" % response['success_count'])
    print("Error Count : %s" % response['error_count'])
    print("Group ID : %s" % response['group_id'])

    if "error_list" in response:
        print("Error List : %s" % response['error_list'])

except CoolsmsException as e:
    print("Error Code : %s" % e.code)
    print("Error Message : %s" % e.msg)
