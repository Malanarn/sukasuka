public class Produk {
    private String kodeProduk;
    private String namaProduk;
    private double harga;

    public Produk(String kode, String nama, double harga) {
        this.kodeProduk = kode;
        this.namaProduk = nama;
        this.harga = harga;
    }

    public String getKode() {
        return kodeProduk;
    }

    public String getNama() {
        return namaProduk;
    }

    public double getHarga() {
        return harga;
    }

    public void tampilkanInfo() {
        System.out.println("Kode : " + getKode());
        System.out.println("Nama : " + getNama());
        System.out.println("Harga: " + getHarga());
        System.out.println("------------------------------");
    }
}
