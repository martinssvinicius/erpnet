@echo off
pg_ctl -D "C:\Program Files\PostgreSQL\16\data" start
start "" /b sass scss/:css/ --watch
php -S localhost:8000 router.php