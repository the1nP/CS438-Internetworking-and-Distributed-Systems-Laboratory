# Exercise: User & Group Management

## โจทย์ (Requirements)

จากรูปภาพโจทย์ (Slide):

1. **สร้างกลุ่มดังต่อไปนี้:**
   - `writers` (GID: 5000)
   - `tv` (GID: 6000)
   - `movie` (GID: 7000)

2. **สร้างบัญชีผู้ใช้ (User accounts):**
   - รายชื่อ: `user1` [1001], `user2` [1002], `user3` [1003], `user4` [1004], `user5` [1005]
   - **เงื่อนไขเพิ่มเติม:**
     - ผู้ใช้ทุกคนต้องมีกลุ่มหลัก (Default group) เป็น `writers`
     - รหัสผ่านเริ่มต้นคือ `cs438_2/2568`
     - Home directory อยู่ที่ `/home/username`
     - `user1`, `user2` ต้องอยู่ในกลุ่ม `tv` ด้วย (Secondary group)
     - ผู้ใช้ที่เหลือ (`user3`, `user4`, `user5`) ต้องอยู่ในกลุ่ม `movie`

---

## คำสั่งที่ใช้ในการทำ (Implementation Commands)

### 1. การสร้าง Group

```bash
sudo groupadd -g 5000 writers
sudo groupadd -g 6000 tv
sudo groupadd -g 7000 movie
```

### 2. การสร้าง User

```bash
# สำหรับ user1 และ user2 (กลุ่มรองคือ tv)
sudo useradd -u 1001 -g 5000 -G 6000 -m -s /bin/bash user1
sudo useradd -u 1002 -g 5000 -G 6000 -m -s /bin/bash user2

# สำหรับ user3, user4 และ user5 (กลุ่มรองคือ movie)
sudo useradd -u 1003 -g 5000 -G 7000 -m -s /bin/bash user3
sudo useradd -u 1004 -g 5000 -G 7000 -m -s /bin/bash user4
sudo useradd -u 1005 -g 5000 -G 7000 -m -s /bin/bash user5
```

### 3. การตั้งรหัสผ่าน (แบบทีละคน หรือ แบบชุดเดียวพร้อมกัน)

**แบบทีละบรรทัด (เข้าใจง่าย):**

```bash
echo "user1:cs438_2/2568" | sudo chpasswd
echo "user2:cs438_2/2568" | sudo chpasswd
echo "user3:cs438_2/2568" | sudo chpasswd
echo "user4:cs438_2/2568" | sudo chpasswd
echo "user5:cs438_2/2568" | sudo chpasswd
```

**แบบชุดเดียวพร้อมกัน (รวดเร็ว/Batch):**

```bash
sudo chpasswd << 'EOF'
user1:cs438_2/2568
user2:cs438_2/2568
user3:cs438_2/2568
user4:cs438_2/2568
user5:cs438_2/2568
EOF
```

---

## วิธีการตรวจสอบ (Verification)

ใช้คำสั่งเหล่านี้เพื่อเช็คความถูกต้อง:

1. **เช็คกลุ่ม:** `getent group writers tv movie`
2. **เช็ครายละเอียด User (UID/GID/Groups):** `id user1` (เปลี่ยนชื่อ user ไปเรื่อยๆ)
3. **เช็ค Home Directory:** `ls -ld /home/user*`
4. **สรุปรายชื่อผู้ใช้ทั้งหมด:** `grep -E "user[1-5]" /etc/passwd`
