// Copyright (c) 2019 Andrey Valyaev <dron.valyaev@gmail.com>
//
// This software may be modified and distributed under the terms
// of the MIT license.  See the LICENSE file for details.

#pragma once

const uint32_t VERSION = 1;

enum Command : uint32_t {
	DIRECTION = 0x80000000,

	// Инвентаризация
	S2C_INVENTORY = 0,
	C2S_INVENTORY = DIRECTION | S2C_INVENTORY,

	// Конфигурация замков
	S2C_CONFIG = 1,
	C2S_CONFIG = DIRECTION | S2C_CONFIG,

	// Состояние ключа
	S2C_KEY_STATUS = 2,
	C2S_KEY_STATUS = DIRECTION | S2C_KEY_STATUS,

	// Закрытие замка
	S2C_LOCK = 3,
	C2S_LOCK = DIRECTION | S2C_LOCK,

	// Открытие замка
	S2C_UNLOCK = 4,
	C2S_UNLOCK = DIRECTION | S2C_UNLOCK,

	S2C_STATE = 5,
	C2S_STATE = DIRECTION | S2C_STATE,

	S2C_IDENT = 6,
};

enum Result: uint32_t {
	FAILURE = 0,
	SUCCESS = 1,
};

enum Aprove: uint32_t {
	REJECT = 0,
	APPROVE = 1,
};

enum State: uint32_t {
	OPENED = 0,
	CLOSED = 1,
};

struct InventoryRequest {
	uint32_t version = VERSION;
	uint32_t command = S2C_INVENTORY;
} __attribute__((packed));

struct InventoryReply {
	uint32_t version = VERSION;
	uint32_t command = C2S_INVENTORY;
	uint32_t lock_count;		// Количество замков
} __attribute__((packed));
// uint32_t locks[];		// Список замков после структуры

struct ConfigRequest {
	uint32_t version = VERSION;
	uint32_t command = S2C_CONFIG;
	uint32_t lock_no;		// Номер замка
	uint32_t timeout;		// Время ожидания ответа от сервера
	uint32_t ntry;			// Количество попыток обращения к серверу
	uint32_t keys_count;		// Количество мастерключей
} __attribute__((packed));
// uint64_t keys[];		// Список мастерключей после структуры

struct ConfigReply {
	uint32_t version = VERSION;
	uint32_t command = C2S_CONFIG;
	uint32_t lock_no;
	uint32_t status;
} __attribute__((packed));

struct KeyStatusRequest {
	uint32_t version = VERSION;
	uint32_t command = C2S_KEY_STATUS;
	uint64_t key;
} __attribute__((packed));

struct KeyStatusReply {
	uint32_t version = VERSION;
	uint32_t command = S2C_KEY_STATUS;
	uint64_t key;
	uint64_t contract;		// Номер договора? в каком формате должен быть?
	uint32_t expired;		// время окончания действия, в секундах с эпохи.
	int32_t money;			// Баланс в копейках (возможны отрицательные значения)
	uint32_t lock_count;		// Количество закрытых ящиков.
} __attribute__((packed));
// uint32_t locks[];		// Список закрытых ящиков после структуры
// Но если мы хотим донести это до пользователя - нужно номер замка странслировать в номер ящика

struct LockRequest {
	uint32_t version = VERSION;
	uint32_t command = C2S_LOCK;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Номер ключа
} __attribute__((packed));

struct LockReply {
	uint32_t version = VERSION;
	uint32_t command = S2C_LOCK;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Номер ключа
	uint32_t approve;		// Подтверждение
	uint32_t time;			// Время закрытия
} __attribute__((packed));

struct UnlockRequest {
	uint32_t version = VERSION;
	uint32_t command = C2S_UNLOCK;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Номер ключа
} __attribute__((packed));

struct UnlockReply {
	uint32_t version = VERSION;
	uint32_t command = S2C_UNLOCK;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Номер ключа
	uint32_t approve;		// Подтверждение
	uint32_t time;			// Время открытия
} __attribute__((packed));

struct StateRequest {
	uint32_t version = VERSION;
	uint32_t command = S2C_STATE;
	uint32_t lock_no;		// Номер замка
} __attribute__((packed));

struct StateReply {
	uint32_t version = VERSION;
	uint32_t command = C2S_STATE;
	uint32_t lock_no;		// Номер замка
	uint64_t key;			// Идентификатор ключа
	uint32_t state;			// Закрыт/открыт State
	uint32_t time;			// Время последнего события
} __attribute__((packed));

struct IdentRequest {
	uint32_t version = VERSION;
	uint32_t command = S2C_IDENT;
	uint32_t lock_no;		// Номер замка
} __attribute__((packed));
