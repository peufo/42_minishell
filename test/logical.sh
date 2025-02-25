ls /not_dir && ls /usr || ls /not_dir || ls /usr
(ls /not_dir && ls /usr || ls /not_dir) || ls /usr
ls /not_dir && ls /usr || (ls /not_dir && ls /not_dir || ls /etc) && ls /usr
