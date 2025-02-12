#!/bin/bash

# مجلد التخزين
TARGET_DIR="Simple"
mkdir -p "$TARGET_DIR"

# البحث عن أكواد C++ عبر GitHub CLI
gh search code --language C++ --limit 50 --json path,repository,url > results.json

# قراءة JSON وجلب الأكواد
jq -c '.[]' results.json | while read -r line; do
    FILE_URL=$(echo $line | jq -r '.url')
    FILE_NAME=$(basename "$(echo $line | jq -r '.path')" | tr -d '[:space:]/\\:*?"<>|')
    REPO_NAME=$(echo $line | jq -r '.repository.name')
    REPO_OWNER=$(echo $line | jq -r '.repository.owner')

    # إنشاء مسار الحفظ
    SAVE_PATH="$TARGET_DIR/${REPO_OWNER}_${REPO_NAME}_$FILE_NAME"

    # تنزيل الكود
    curl -sL "$FILE_URL" -o "$SAVE_PATH"

    # التحقق مما إذا كان الملف تم تنزيله بنجاح
    if [ ! -f "$SAVE_PATH" ]; then
        echo "❌ فشل في تنزيل الملف: $FILE_NAME"
        continue
    fi

    # حساب عدد الأسطر
    LINE_COUNT=$(wc -l < "$SAVE_PATH")

    # تصنيف الملفات حسب عدد الأسطر
    if [ "$LINE_COUNT" -le 100 ]; then
        echo "✅ حفظ الملف: $SAVE_PATH ($LINE_COUNT سطر)"
    else
        echo "❌ تجاوز الحد (> $LINE_COUNT سطر)، حذف الملف"
        rm "$SAVE_PATH"
    fi
done

# إضافة الملفات إلى المستودع
git add Simple/
git commit -m "Added C++ codes with LOC ≤ 100"
git push origin main
