#!/bin/bash
#GET  https://app.aurassure.com/-/api/iot-platform/v1.1.0/clients/16440/applications/16/things/list
#Access-Id
#VZtfmAzlJwjv4o6B
#Access-Key
#CeO0vLPfWYoc3wGZ3H7KH5Y1MkCeaeoDZXJZC3o5frr2b7tVHWpljAiRHf5HfuHp


# Replace with your actual Access credentials
ACCESS_ID="VZtfmAzlJwjv4o6B"
ACCESS_KEY="CeO0vLPfWYoc3wGZ3H7KH5Y1MkCeaeoDZXJZC3o5frr2b7tVHWpljAiRHf5HfuHp"


# API Endpoint
URL="https://app.aurassure.com/-/api/iot-platform/v1.1.0/clients/16440/applications/16/things/list"


# Execute curl GET request
curl -X GET "$URL" \
  -H "Access-Id: $ACCESS_ID" \
  -H "Access-Key: $ACCESS_KEY" \
  -H "Accept: application/json"

