# User Documentation

## Overview

This project provides a secure WordPress website accessible via HTTPS.  
The infrastructure consists of the following services:

- **NGINX** – Web server and reverse proxy (TLSv1.2 / TLSv1.3 only)
- **WordPress + PHP-FPM** – Handles dynamic content and PHP execution
- **MariaDB** – Stores WordPress database

All services run in their own containers and communicate through a private Docker network.

---

## Starting and Stopping the Project

### Start the infrastructure
```bash
make
```

### Stop the infrastructure
```bash
make down
```

### Stop and remove all containers, images, and volumes
```bash
make fclean
```

---

## Accessing the Website

- **Website URL:** https://mgobert.42.fr
- **WordPress Admin Panel:** https://mgobert.42.fr/wp-admin

**Note:** Replace `mgobert` with your own 42 login if needed.

---

## Credentials Management

All credentials are stored in a local `.env` file at the root of the project:

- Database name, user, and password
- WordPress administrator credentials
- Secondary WordPress user credentials

**Important:** The `.env` file is ignored by Git and should never be pushed to the repository.

---

## Checking Services Status

### List running containers
```bash
docker compose ps
```

### View logs of all containers
```bash
docker compose logs -f
```

### Verify volumes
```bash
docker volume ls
```

---

## Troubleshooting

- Ensure Docker and Docker Compose are installed correctly
- Make sure port 443 is free on your machine
- Verify that the domain name points to your local IP address (`/etc/hosts` if necessary)
- If the website is not accessible, check the container logs for errors
- Confirm that the WordPress database is running and initialized

---