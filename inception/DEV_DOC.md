# Developer Documentation

## Prerequisites

- Linux virtual machine
- Docker
- Docker Compose
- Make

---

## Project Structure

```
.
├── Makefile
├── docker-compose.yml
├── .env                 # ignored by git
├── srcs/
│   ├── mariadb/
│   ├── wordpress/
│   └── nginx/
└── data/
    ├── mariadb/
    └── wordpress/
```

---

## Environment Setup

### 1. Clone the repository
```bash
git clone <repository_url>
cd <repository_name>
```

### 2. Create a .env file based on .env.example
```bash
cp .env.example .env
```

### 3. Create persistent data directories
```bash
mkdir -p /home/mgobert/data/mariadb
mkdir -p /home/mgobert/data/wordpress
```

**Note:** Replace `mgobert` with your own 42 login.

---

## Build and Launch

### Build images and start containers
```bash
make
```

### Rebuild the entire project
```bash
make re
```

### Stop containers
```bash
make down
```

### Remove all containers, volumes, and images
```bash
make fclean
```

---

## Useful Docker Commands

### List running containers
```bash
docker compose ps
```

### View logs
```bash
docker compose logs -f
```

### Enter a container shell
```bash
docker exec -it nginx bash
```

---

## Data Persistence

**MariaDB data** is stored in:
```
/home/mgobert/data/mariadb
```

**WordPress website files** are stored in:
```
/home/mgobert/data/wordpress
```

These directories ensure data persists even after stopping or removing containers.

---

## Developer Notes

- No passwords are hardcoded in Dockerfiles or scripts
- Containers follow PID 1 best practices and run a single main process
- Only port 443 is exposed to the host
- Internal communication between containers uses a Docker bridge network
- Environment variables in `.env` configure the project and are ignored by Git

---