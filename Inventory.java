public class Inventory {
    private Produk[] daftarProduk = new Produk[10];
    private int jumlah = 0;

    public void addProduk(Produk p) {
        if (jumlah < daftarProduk.length) {
            daftarProduk[jumlah] = p;
            jumlah++;
        }
    }

    public void tampilProduk() {
        System.out.println("=== Data Produk di Inventory ===");
        for (int i = 0; i < jumlah; i++) {
            daftarProduk[i].tampilkanInfo();
        }
    }

    public Produk cariProduk(String kode) {
        for (int i = 0; i < jumlah; i++) {
            if (daftarProduk[i].getKode().equalsIgnoreCase(kode)) {
                return daftarProduk[i];
            }
        }
        return null;
    }
}
