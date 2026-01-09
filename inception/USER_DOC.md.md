# User Documentation

This guide explains how to use the Inception project infrastructure.

---

## Services Provided

The stack consists of three services:

- **NGINX** – Web server with HTTPS encryption (secure access to the website)
- **WordPress + PHP-FPM** – Website platform with content management
- **MariaDB** – Database storing all website data (posts, users, settings, etc.)

All services run in isolated containers and communicate through a private network.

---

## Starting and Stopping

### Start the infrastructure
```bash
make
```

### Stop the infrastructure
```bash
make down
```

### Stop and remove all data (full cleanup)
```bash
make fclean
```

---

## Accessing the Website and Admin Panel

- **Website:** https://mgobert.42.fr
- **Admin Panel:** https://mgobert.42.fr/wp-admin

*Replace `mgobert` with your login if needed.*

**Note:** Ignore certificate warnings—they are normal in development environments.

---

## Locating and Managing Credentials

All credentials are stored in the `.env` file at the project root:

```
MYSQL_ROOT_PASSWORD=<root_password>
MYSQL_USER=<database_username>
MYSQL_PASSWORD=<database_password>
MYSQL_DATABASE=<database_name>
```

**Security:** Keep the `.env` file private and never commit it to Git.

---

## Checking Services Are Running

### View service status
```bash
docker compose ps
```

All three services should show as "Up".

### View service logs
```bash
docker compose logs -f
```

Press `Ctrl+C` to exit.

### Test the website
1. Open https://mgobert.42.fr
2. Try logging in at https://mgobert.42.fr/wp-admin

---

## Quick Troubleshooting

| Issue | Solution |
|-------|----------|
| Website won't load | Check `docker compose ps` and `docker compose logs` |
| Database connection error | Verify `.env` credentials and restart with `make down && make` |
| Admin panel blank | Clear browser cache and refresh |
| Certificate warning | This is normal—proceed to the site anyway |

---

## Summary

| Task | Command |
|------|---------|
| Start | `make` |
| Stop | `make down` |
| Status | `docker compose ps` |
| Logs | `docker compose logs -f` |
