<?php
include 'koneksi.php';

if(!isset($_GET['uid']) || $_GET['uid']==""){
    echo "NO_UID";
    exit();
}

$uid = $_GET['uid'];
$tarif = 5000;

$q = mysqli_query($conn,"SELECT * FROM users WHERE uid='$uid'");

// auto register
if(mysqli_num_rows($q)==0){

    mysqli_query($conn,
    "INSERT INTO users(uid,nama,saldo)
    VALUES('$uid','User',50000)");

    echo "OK";
    exit();
}

$data = mysqli_fetch_assoc($q);

if($data['saldo'] >= $tarif){

    mysqli_query($conn,
    "UPDATE users SET saldo = saldo - $tarif WHERE uid='$uid'");

    echo "OK";

} else {
    echo "NO";
}
?>