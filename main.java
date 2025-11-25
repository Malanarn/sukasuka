public class Main {
    public static void main(String[] args) {

        Produk p1 = new Produk("AB2001911", "Air Bag", 400);
        Produk p2 = new Produk("SW20030909", "Steering Wheel", 1000);
        Produk p3 = new Produk("HB07112004", "Hand Brake", 1000);
        Produk p4 = new Produk("FP9112001", "Fuel Pump", 900);

        Inventory inv = new Inventory();

        inv.addProduk(p1);
        inv.addProduk(p2);
        inv.addProduk(p3);
        inv.addProduk(p4);

        inv.tampilProduk();

        System.out.println("\n=== Hasil Pencarian ===");
        Produk hasil = inv.cariProduk("SW20030909");

        if (hasil != null) {
            System.out.println("Kode : " + hasil.getKode());
            System.out.println("Nama : " + hasil.getNama());
            System.out.println("Harga: " + hasil.getHarga());
        } else {
            System.out.println("Produk tidak ditemukan!");
        }
    }
}
