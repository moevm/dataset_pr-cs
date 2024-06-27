for file in test/*; do
    [[ -f "$file" ]] || continue
    echo "------------------------"
    echo "-- test: $file --"
    echo "------------------------"
    cat "$file"
    src/cw < "$file"
done
