#!/bin/bash

# Цвета для вывода
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Функция для вывода сообщения об успешном выполнении
print_success() {
    printf "${GREEN}%s${NC}\n" "$1"
}


print_warning() {
    printf "${YELLOW}%s${NC}\n" "$1"
}


print_error() {
    printf "${RED}%s${NC}\n" "$1" >&2
}


check_package() {
    if ! command -v "$1" &> /dev/null; then
        print_warning "$1 не установлен. Устанавливаем..."
        sudo apt-get install "$1" -y || {
            print_error "Ошибка при установке $1."
            exit 1
        }
    else
        print_success "$1 установлен."
    fi
}


check_package "doxygen"
check_package "dot"
check_package "g++"


print_success "Обновляем репозиторий Git..."
git pull origin main || {
    print_error "Ошибка при обновлении репозитория Git."
    exit 1
}


print_success "Обновляем submodule Git..."
git submodule update --recursive --remote || {
    print_error "Ошибка при обновлении submodule Git."
    exit 1
}

print_success "Скрипт выполнен."
