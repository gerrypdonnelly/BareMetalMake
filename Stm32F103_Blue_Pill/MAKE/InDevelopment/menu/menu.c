#include <stdint.h>

/* ================= USER HARDWARE STUBS ================= */
/* Replace these with your real LCD + GPIO code */

void lcd_clear(void) {}
void lcd_set_cursor(uint8_t col, uint8_t row) {}
void lcd_print(const char *str) {}

uint8_t button_forward_pressed(void) { return 0; }
uint8_t button_back_pressed(void)    { return 0; }
uint8_t button_select_pressed(void)  { return 0; }

/* ======================================================= */


/* ================= MENU STRUCTURE ====================== */

typedef struct MenuItem {
    const char *name;
    struct MenuItem *parent;
    struct MenuItem *children;
    uint8_t numChildren;
    void (*action)(void);
} MenuItem;


/* ================= ACTION FUNCTIONS ==================== */

void action_start(void) {
    /* Start watering */
}

void action_stop(void) {
    /* Stop watering */
}

void action_set_watering_time(void) {
    /* Enter watering time edit mode */
}

void action_set_min_moisture(void) {
    /* Edit minimum moisture */
}

void action_set_max_moisture(void) {
    /* Edit maximum moisture */
}


/* ================= MENU DEFINITIONS ==================== */
/* Bottom-up definitions */

/* Trigger moisture */
MenuItem menu_trigger_moisture = {
    .name = "Trigger moisture",
    .children = 0,
    .numChildren = 0,
    .action = 0
};

/* Watering time */
MenuItem menu_watering_time_children[] = {
    {
        .name = "Trigger moisture",
        .children = 0,
        .numChildren = 0,
        .action = 0
    }
};

MenuItem menu_watering_time = {
    .name = "Watering time",
    .children = menu_watering_time_children,
    .numChildren = 1,
    .action = 0
};

/* Set min / max moisture */
MenuItem menu_set_max_moisture = {
    .name = "Set max moisture",
    .children = 0,
    .numChildren = 0,
    .action = action_set_max_moisture
};

MenuItem menu_set_min_children[] = {
    {
        .name = "Set max moisture",
        .children = 0,
        .numChildren = 0,
        .action = action_set_max_moisture
    }
};

MenuItem menu_set_min_moisture = {
    .name = "Set min moisture",
    .children = menu_set_min_children,
    .numChildren = 1,
    .action = action_set_min_moisture
};

/* Settings */
MenuItem menu_settings_children[] = {
    {
        .name = "Start",
        .children = 0,
        .numChildren = 0,
        .action = action_start
    },
    {
        .name = "Watering time",
        .children = menu_watering_time_children,
        .numChildren = 1,
        .action = 0
    },
    {
        .name = "Set min moisture",
        .children = menu_set_min_children,
        .numChildren = 1,
        .action = action_set_min_moisture
    }
};

MenuItem menu_settings = {
    .name = "Settings",
    .children = menu_settings_children,
    .numChildren = 3,
    .action = 0
};

/* Calibration */
MenuItem menu_calibration_children[] = {
    {
        .name = "Settings",
        .children = menu_settings_children,
        .numChildren = 3,
        .action = 0
    }
};

MenuItem menu_calibration = {
    .name = "Calibration",
    .children = menu_calibration_children,
    .numChildren = 1,
    .action = 0
};

/* Stop */
MenuItem menu_stop_children[] = {
    {
        .name = "Calibration",
        .children = menu_calibration_children,
        .numChildren = 1,
        .action = 0
    }
};

MenuItem menu_stop = {
    .name = "Stop",
    .children = menu_stop_children,
    .numChildren = 1,
    .action = action_stop
};

/* Auto */
MenuItem menu_auto_children[] = {
    {
        .name = "Stop",
        .children = menu_stop_children,
        .numChildren = 1,
        .action = action_stop
    }
};

MenuItem menu_auto = {
    .name = "Auto",
    .children = menu_auto_children,
    .numChildren = 1,
    .action = 0
};

/* Watering */
MenuItem menu_watering_children[] = {
    {
        .name = "Auto",
        .children = menu_auto_children,
        .numChildren = 1,
        .action = 0
    }
};

MenuItem menu_watering = {
    .name = "Watering",
    .children = menu_watering_children,
    .numChildren = 1,
    .action = 0
};

/* Hello Screen (Root) */
MenuItem menu_hello_children[] = {
    {
        .name = "Watering",
        .children = menu_watering_children,
        .numChildren = 1,
        .action = 0
    }
};

MenuItem menu_hello = {
    .name = "Hello Screen",
    .children = menu_hello_children,
    .numChildren = 1,
    .action = 0
};


/* ================= MENU ENGINE ========================= */

MenuItem *currentMenu = &menu_hello;
uint8_t selectedIndex = 0;

/* Assign parent pointers recursively */
void menu_assign_parents(MenuItem *menu) {
    for (uint8_t i = 0; i < menu->numChildren; i++) {
        menu->children[i].parent = menu;
        if (menu->children[i].numChildren > 0) {
            menu_assign_parents(&menu->children[i]);
        }
    }
}

/* Button actions */
void menu_forward(void) {
    selectedIndex++;
    if (selectedIndex >= currentMenu->numChildren)
        selectedIndex = 0;
}

void menu_back(void) {
    if (currentMenu->parent) {
        currentMenu = currentMenu->parent;
        selectedIndex = 0;
    }
}

void menu_select(void) {
    MenuItem *sel = &currentMenu->children[selectedIndex];
    if (sel->numChildren > 0) {
        currentMenu = sel;
        selectedIndex = 0;
    } else if (sel->action) {
        sel->action();
    }
}

/* Draw menu (16x2 LCD assumed) */
void menu_draw(void) {
    lcd_clear();
    for (uint8_t i = 0; i < currentMenu->numChildren && i < 2; i++) {
        lcd_set_cursor(0, i);
        lcd_print(i == selectedIndex ? ">" : " ");
        lcd_print(currentMenu->children[i].name);
    }
}

/* ================= INITIALIZATION ====================== */

void menu_init(void) {
    menu_assign_parents(&menu_hello);
    menu_draw();
}

/* ================= MAIN LOOP CALL ====================== */
/* Call this periodically (e.g. every 20–50ms) */

void menu_task(void) {
    if (button_forward_pressed()) {
        menu_forward();
        menu_draw();
    }

    if (button_back_pressed()) {
        menu_back();
        menu_draw();
    }

    if (button_select_pressed()) {
        menu_select();
        menu_draw();
    }
}
