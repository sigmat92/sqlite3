TOKEN=$(curl -s -X POST "https://coddleonline.com/example/user/login" \
  -H "Content-Type: application/json" \
  -d '{"username":"Tnhmis_VitalMachine","password":"1234567"}' | jq -r '.token')

echo $TOKEN

curl -X POST "https://coddleonline.com/HISIntegrationMachine/api/v1/vital-details" \
  -H "Authorization: Bearer $TOKEN" \
  -H "Content-Type: application/json" \
  -d '{
        "mId": "0004",
        "pId": "4321",
        "entry_date": "27/02/2026",
	"hospital_code":"123456",
	"hmis_code":"12345689",
        "mobile_no": "9820856498",
        "name": "Prakash D",
        "age": "56",
        "sex": "Male",
        "height": "175",
        "weight": "75",
        "bmi": "24.5",
        "bmr": "1500",
        "bsa": "1.9",
        "temp": "98.6",
        "systolic_bp": "120",
        "diastolic_bp": "80",
        "map": "93",
        "spo2": "98",
        "pr": "72",
	"gnum_isvalid":"yes",
	"seatId":"123"
      }'
