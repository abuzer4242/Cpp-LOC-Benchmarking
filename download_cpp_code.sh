#!/bin/bash

# الدليل الذي سيتم حفظ الأكواد فيه
OUTPUT_DIR="Simple"
mkdir -p "$OUTPUT_DIR"

# استعلام GitHub API لجلب ملفات C++ فقط
REPO="abuzer4242/Cpp-LOC-Benchmarking"  # تأكد من أنه المستودع الصحيح
BRANCH="main"
FILES=$(gh api repos/$REPO/git/trees/$BRANCH?recursive=1 | jq -r '.tree[] | select(.type=="blob") | .path')

# تحميل كل ملف والتحقق من امتداده
echo "$FILES" | while read -r line; do
    # استخراج اسم الملف وإزالة الأحرف غير المرغوبة
    FILE_NAME=$(basename "$(echo $line | jq -r '.path')" | tr -d '[:space:]/\\:*?"<>|')

    # التحقق من أن الملف ينتهي بـ .cpp فقط
    if [[ "$FILE_NAME" != *.cpp ]]; then
        echo "⚠️ تخطي الملف غير المناسب: $FILE_NAME"
        continue
    fi

    # تنزيل الملف إلى الدليل المطلوب
    FILE_URL="https://raw.githubusercontent.com/$REPO/$BRANCH/$line"
    curl -s "$FILE_URL" -o "$OUTPUT_DIR/$FILE_NAME"

    echo "✅ تم تنزيل الملف: $FILE_NAME"
done

echo "🎉 تم الانتهاء من تنزيل جميع ملفات C++ بنجاح!"
