## lab1

## lab2

## lab3
1. Viết mô-đun nhân thực hiện các công việc sau:
```
- Tính tích vô hướng của 2 vector
- Tính tổng, hiệu, tích 2 ma trận
- Tính chỉnh hợp chập k của N
```

2. Viết mô-đun nhân một số hàm mật mã đơn giản

```
- Thực hiện mã hóa chuyển vị
    + Dữ liệu rõ chứa trong XauRo
    + Khóa K: chứa trong biến nhớ k
    + Dữ liệu mã chứa trong XauMa
- Thực hiện mã hóa thay thế
    + Dữ liệu rõ chứa trong XauRo
    + Khóa K: mảng các ký tự được thay thế tương ứng
    + Dữ liệu mã chứa trong XauMa
- Thực hiện mã hóa hoán vị toàn cục
    + Dữ liệu rõ chứa trong XauRo
    + Khóa K: mảng các chỉ số hoán vị tương ứng
    + Dữ liệu mã chứa trong XauMa
```

## lab4
1. Viết 1 character driver theo cách cấp phát device number động, tên driver = lab4.1 + tên sinh viên. Và viết chương trình sử dụng driver này từ không gian người dùng.4
2. Viết 1 character driver theo cách cấp phát device number tĩnh, tên driver = lab4.2 +
tên sinh viên. Và viết chương trình sử dụng driver này từ không gian người dùng.

## lab5
1.   Viết 1 character driver theo cách cấp phát device number động, tên driver = lab5.1 + tên
    sinh viên. Driver thực hiện công việc sau: cung cấp hàm nhận 1 số hệ 10 từ không gian
    người dùng, chuyển số hệ 10 sang hệ 2, 8, 16 và lưu ra thiết bị; cho phép đọc các số hệ 10,
    2, 8, 16 tương ứng.</br>
    Viết chương trình người dùng thực hiện menu chức năng sau:</br>

```
1. Open thiết bị
2. Nhập số hệ 10 và ghi ra thiết bị số hệ 10, 2, 8, 16
3. Đọc số hệ 2
4. Đọc số hệ 8
5. Đọc số hệ 16
6. Đóng thiết bị và kết thúc ctr
```

2.  Viết 1 character driver theo cách cấp phát device number động, tên driver = lab5.2 + tên
    sinh viên. Driver thực hiện việc lấy thời gian tuyệt đối (trong nhân) chính xác đến micro
    giây, nano giây và thời gian tương đối.</br>
    Viết chương trình người dùng thực hiện menu chức năng sau:</br>

```
1. Lấy thời gian tuyệt đối, chính xác đến micro giây2. Lấy thời gian tuyệt đối, chính xác đến nano giây
3. Lấy thời gian tương đối
4. Kết thúc ctr
```

## lab6
Viết 1 driver mật mã dạng Character driver cài đặt một số thuật toán mã hoá như: mã dịch chuyển, mã hoán vị, mã thay thế.</br>
Viết chương trình người dùng sử dụng thư viện mật mã trên theo menu chức năng sau</br>

```
1. Nhập vào 1 xâu.
2. Mã hoá và lưu xâu mã dùng mã dịch chuyển (khoá nhập vào từ bàn phím).
3. Mã hoá và lưu xâu mã dùng mã thay thế (khoá nhập vào từ bàn phím).
4. Mã hoá và lưu xâu mã dùng mã hoán vị (khoá nhập vào từ bàn phím).
5. Giải mã theo dịch chuyển.
6. Giải mã theo hoán vị.
7. Giải mã thay thế.
```

## lab7
Viết 1 driver mật mã dạng Character driver cài đặt một số thuật toán băm: MD5, SHA1, SHA2. </br>
Viết chương trình người dùng sử dụng thư viện mật mã trên theo menu chức năng sau:</br>
Menu chức năng:</br>

```
1. Nhập vào danh sách người dùng (lưu ra file: gồm tên đăng nhập; mật khẩu được băm theo 3 thuật toán trên)
2. xoá người dùng khỏi danh sách
3. Kiểm tra đăng nhập: cho phép chọn thuật toán băm ở trên; nhập tên đăng nhập và mật khẩu; cần băm mật khẩu để so sánh theo thuật toán băm tương ứng.
4. thoát.
```