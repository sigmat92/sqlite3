TOKEN=$(curl -s -X POST "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/authenticate/UserId/Password" \
  -H "Content-Type: application/json" \
  -d '{"username":"Tnhmis_VitalMachine","password":"1234567"}' | jq -r '.token')

echo $TOKEN

curl -X POST "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/api/v1/vital-details" \
  -H "Authorization: Bearer $TOKEN" \
  -H "Content-Type: application/json" \
  -d '{
"mId": "2434",
"pId": "4125",
"entry_date":"27-02-2026",
"hospital_code":"123456",
"hmis_code": "202",
"mobile_no": "9876543210",
"name": "Prakash Dhrutaraj",
"age": "30",
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
"gnum_isvalid": "yes",
"seatId":"123"
}'
