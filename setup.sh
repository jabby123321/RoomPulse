#!/bin/bash
set -e

echo "Setting up RoomPulse..."

# check dependencies
missing_deps=false
if ! command -v  docker &> /dev/null; then
  echo "Missing dependency - docker"
  missing_deps=true
fi
if ! command -v docker-compose &> /dev/null; then
  echo "Missing dependency - docker-compose"
  missing_deps=true
fi
if $missing_deps then
  exit 1
fi
if ! command -v node &> /dev/null; then
  echo "Missing dependency - node.js"
  missing_deps=true
fi
if $missing_deps then
  exit 1
fi
if ! command -v npm &> /dev/null; then
  echo "Missing dependency - npm"
  missing_deps=true
fi
if $missing_deps then
  exit 1
fi

echo "Building front-end..."
cd Services/web
npm install
npm run build
cd ../../

echo "Building back-end..."
cd Services/web
npm install
cd ../../

echo "Starting all services with docker compose..."
cd Infrastructure/docker
docker-compose up --build -d

sleep 10

echo "Setup Complete"
LOCAL_IP=$(hostname -i | awk '{print $1}')




