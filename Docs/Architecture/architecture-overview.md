# Architecture overview

Table of contents:


- [1 Introduction](#1-introduction)
- [2 Back-end](#2-back-end)
  - [2.1 Technology Stack](#21-technology-stack)
- [3 Database](#3-database)
  - [3.1 Technology Stack](#31-technology-stack)
- [4 Front-end](#4-front-end)
  - [4.1 Technology Stack](#41-technology-stack)
- [5 Firmware](#5-firmware)
  - [5.1 Technology Stack](#51-technology-stack)
- [6 Infrastructure](#6-infrastructure)
  - [6.1 Technology Stack](#61-technology-stack)
- [7 Data Flow](#7-data-flow)
- [8 Non-Functional Considerations](#8-non-functional-considerations)

## 1 Introduction

Roompulse is an IoT sensor aggregation platform consisting of embedded IoT firmware, a back-end API, relational and time-series database and a browser-based front-end.

IoT devices collect sensor readings and transmit them to the back-end API. The API back-end validates the data and persists it to the database solution. The front-end retrieves the stored data via the API for visualisation.

This document describes the high-level architecture of RoomPulse defining system components, their responsibilities, and their interactions.

![Component diagram showing system architecture](.images/component-diagram.png)

## 2 Back-end

The API acts as an interface for an IoT device to store data as well as for the front-end to retreive sensor data, register new IoT devices.

It provides endpoints for:
- Sensor devices to authenticate and submit batched readings
- Users to retrieve historical and aggregated sensor data
- Device registration and management
- User authentication and authorisation
- User management

The back-end API also performs request validation and authentication and persistence to the database. It does not render UI content or communicate with hardware except for HTTPS requests.

### 2.1 Technology Stack

- Platform: Node.JS
- Language: TypeScript
- Framework: Express.js
- Package Manager: npm
- API Style: REST
- API Specification: OpenAPI
- API Documentation: SwaggerUI

## 3 Database

The database system stores relational data such as user data and sensor/device metadata as well as sensor readings in the form of time-series data.

The database system is responsible for:
- Storage of device metadata including:
  - Device Sensors (inc metadata e.g sensor type and ID)
  - Device API Keys
  - Device Owner
- Storage of (time-series) sensor readings
- Storage of user accounts and related metadata

### 3.1 Technology Stack

- Database: PostgreSQL
  - TimescaleDB Extension

## 4 Front-end

The front-end system is the point at which the user interacts with the system via a web browser. It retreives data from the back-end API to present to the user.

The front-end is responsible for:
- Rendering a user-interface
- Allowing users to authenticate their session
- Allowing users to review data in tables and charts

### 4.1 Technology Stack
- UI Library: React
- Build Tool: Vite
- Hosting: Nginx

## 5 Firmware

The firmware project currently only targets the ESP32. The firmware should be able to collect data from its GPIO interface and transmits batched readings to the back-end API over HTTPS.

The firmware is responsible for:
- Collecting sensor data
- Storing local configuration parameters
- Uploading batched sensor data to the API

### 5.1 Technology Stack

- Hardware: ESP32
- Framework: Arduino Core for ESP32
- Build system: PlatformIO
- Documentation: Doxygen
- Authentication: pre-loaded API keys

## 6 Infrastructure

Roompulse is deployed as a containerised application stack using Docker. All services run on a single host orchestrated using Docker Compose.

Each major system is packaged as an independent container:
- Back-end API
- Front-end Application
- Database system
- Nginx reverse proxy

All services communicate over an internal Docker network. Docker Compose defines and coordinates this multi-container deployment.

### 6.1 Technology Stack

- Containerisation: Docker
- Service Orchestration: Docker Compose
- Reverse Proxy: Nginx

## 7 Data Flow

There are 2 main data flow activities. Data ingestion from IoT devices transmitting readings and queries from the web front-end.

### 7.1 Ingestion Flow
ESP32 -> HTTPS -> Back-end API -> PostgreSQL (TimescaleDB)

### 7.2 Query Flow
User → Browser → Front-end → Back-end API → PostgreSQL

## 8 Non-Functional Considerations
- The system is designed for moderate to low volumes of readings
- The system is not specifically designed for high-availability deployments
- Authentication for sensor devices is performed using pre-loaded API keys generated at device registration
- Although deployed as a single-node system the architecture allows for future flexibility in deployment
