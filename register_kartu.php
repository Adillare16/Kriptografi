<?php
include 'koneksi.php';

$uid = $_GET['uid'];
$nama = $_GET['nama'];
$saldo = $_GET['saldo'];

$query = mysqli_query($conn,
"INSERT INTO users(uid,nama,saldo)
VALUES('$uid','$nama','$saldo')");

if($query){
    echo "Registrasi berhasil";
}else{
    echo "Gagal registrasi";
}
?>