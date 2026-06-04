<?php
include 'koneksi.php';

$uid = $_GET['uid'];
$tambah = $_GET['saldo'];

mysqli_query($conn,
"UPDATE users
SET saldo = saldo + '$tambah'
WHERE uid='$uid'");

echo "Topup berhasil";
?>