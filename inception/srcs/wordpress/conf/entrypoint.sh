#!/bin/bash
set -e

cd /var/www/html

# Supprimer la page par défaut
rm -f index.html

# Télécharger WordPress si absent
if [ ! -f wp-config.php ]; then
    wp core download --allow-root

    wp config create --allow-root \
        --dbname="$MYSQL_DATABASE" \
        --dbuser="$MYSQL_USER" \
        --dbpass="$MYSQL_PASSWORD" \
        --dbhost="$DB_HOST"

    wp core install --allow-root \
        --url="$WP_URL" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL"

    wp user create "$WP_USER2" "$WP_USER2_EMAIL" \
        --user_pass="$WP_USER2_PASSWORD" \
        --role=editor \
        --allow-root
fi

exec "$@"
