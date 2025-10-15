import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Karyawan kry = new Karyawan();

        System.out.print("Masukkan NIK              : ");
        String nik = input.nextLine();
        kry.setNik(nik);

        System.out.print("Masukkan Nama             : ");
        String nama = input.nextLine();
        kry.setNama(nama);

        System.out.print("Masukkan Jabatan          : ");
        String jabatan = input.nextLine();
        kry.setJabatan(jabatan);

        System.out.println("\n=============================");
        System.out.println("Data Karyawan Berhasil Disimpan");
        System.out.println("=============================");
        System.out.println("NIK     : " + kry.getNik());
        System.out.println("Nama    : " + kry.getNama());
        System.out.println("Jabatan : " + kry.getJabatan());

        System.out.println("\nApakah Anda ingin mengubah jabatan?");
        System.out.println("1. Ya");
        System.out.println("2. Tidak");
        System.out.print("Masukkan pilihan Anda : ");

        int pilihan = input.nextInt();
        input.nextLine();

        if (pilihan == 1) {
            System.out.print("Masukkan Jabatan Baru     : ");
            String jabatanBaru = input.nextLine();
            kry.setJabatan(jabatanBaru);
            kry.setJabatanBaru(jabatanBaru);

            System.out.println("\nJabatan berhasil diubah.");
            System.out.println("Data Karyawan setelah diupdate:");
            System.out.println("NIK     : " + kry.getNik());
            System.out.println("Nama    : " + kry.getNama());
            System.out.println("Jabatan : " + kry.getJabatan());
        } else {
            System.out.println("Terima kasih.");
        }

        input.close();
    }
}
