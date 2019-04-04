// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once
#include <arpa/inet.h>

const uint32_t VERSION = 1;

enum Command : uint32_t {
	OK = 1,
	ERROR = 2,

	// Инвентаризация
	INVENTORY_REQ = 3,
	INVENTORY = 4,

	// Конфигурация замков
	CONFIG = 5,

	// Состояние ключа
	KEY_STATUS_REQ = 6,
	KEY_STATUS = 7,

	// Закрытие замка
	LOCK = 8,

	// Открытие замка
	UNLOCK = 9,

	LOCK_STATE_REQ = 10,
	LOCK_STATE = 11,

	IDENT = 12,
};

enum State: uint32_t {
	OPENED = 0,
	CLOSED = 1,
};

struct Ok {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(OK);
	uint32_t id = 0;
	// Дополнительное поле, содержимое зависит от запроса
	uint32_t opt = 0;
};

struct Error {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(ERROR);
	uint32_t id = 0;
};

struct InventoryReq {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(INVENTORY_REQ);
	uint32_t id = 0;
} __attribute__((packed));

struct Inventory {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(INVENTORY);
	uint32_t id = 0;
} __attribute__((packed));
	// uint32_t lock_count = 0;	// Количество замков
	// uint32_t locks[];		// Список замков после структуры

struct Config {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(CONFIG);
	uint32_t id = 0;
	uint32_t lock_no;		// Номер замка
	uint32_t timeout;		// Время ожидания ответа от сервера
	uint32_t ntry;			// Количество попыток обращения к серверу
	uint32_t keys_count;		// Количество мастерключей
} __attribute__((packed));
// uint64_t keys[];		// Список мастерключей после структуры

struct KeyStatusRequest {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(KEY_STATUS_REQ);
	uint32_t id = 0;
	uint64_t key;
} __attribute__((packed));

struct KeyStatus {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(KEY_STATUS);
	uint32_t id = 0;
	uint64_t key = 0;
	uint64_t contract = 0;			// Номер договора? в каком формате должен быть?
	uint32_t expired = 0xffffffff;		// время окончания действия, в секундах с эпохи.
	int32_t money = 0;			// Баланс в копейках (возможны отрицательные значения)
	uint32_t lock_count = 0;		// Количество закрытых ящиков.
} __attribute__((packed));
// uint32_t locks[];		// Список закрытых ящиков после структуры
// Но если мы хотим донести это до пользователя - нужно номер замка странслировать в номер ящика

struct Lock {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(LOCK);
	uint32_t id = 0;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Номер ключа
} __attribute__((packed));

struct Unlock {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(UNLOCK);
	uint32_t id = 0;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Номер ключа
} __attribute__((packed));

struct LockStateReq {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(LOCK_STATE_REQ);
	uint32_t id = 0;
	uint32_t lock_no;		// Номер замка
} __attribute__((packed));

struct LockState {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(LOCK_STATE);
	uint32_t id = 0;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Идентификатор ключа
	uint32_t state;			// Закрыт/открыт State
	uint32_t time;			// Время последнего события
} __attribute__((packed));

struct Ident {
	uint32_t version = htonl(VERSION);
	uint32_t command = htonl(IDENT);
	uint32_t id = 0;
	uint32_t lock_no;		// Номер замка
} __attribute__((packed));
