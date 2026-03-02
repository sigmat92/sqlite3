TOKEN=$(curl -s -X POST "https://coddleonline.com/example/user/login" \
  -H "Content-Type: application/json" \
  -d '{"username":"Tnhmis_VitalMachine","password":"1234567"}' | jq -r '.token')

echo $TOKEN

curl -X GET "https://coddleonline.com/example/user/secure-data" \
  -H "Authorization: Bearer $TOKEN" \
  -H "Content-Type: application/json" \
  
