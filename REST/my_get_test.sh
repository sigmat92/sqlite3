#!/bin/bash

BASE_URL="https://coddleonline.com"

# Step 1: Generate Token
TOKEN=$(curl -s -X POST "$BASE_URL/coddeleonline.com/example/user/login" \
  -H "Content-Type: application/json" \
  -d '{"username":"Tnhmis_VitalMachine","password":"1234567"}' | jq -r '.token')

echo "Token Generated"

# Step 2: Call GET API
#curl -X GET "$BASE_URL/HISIntegrationMachine/api/v1/vital-details?mId=2434&pId=4125" \
#  -H "Authorization: Bearer $TOKEN" \
#  -H "Content-Type: application/json"
