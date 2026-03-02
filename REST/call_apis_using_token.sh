TOKEN=$(curl -s -X POST "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/authenticate/UserId/Password" \
  -H "Content-Type: application/json" \
  -d '{"username":"Tnhmis_VitalMachine","password":"1234567"}' | jq -r '.token')

echo $TOKEN



