import React from "react";
import MenuItem from "./MenuItem";

const Menu = ({ activeMenu, onMenuClick }) => {
  const menuItems = [
    "Home",
    "About the Project",
    "Choose Pattern",
    "Create your Pattern",
    "Contact",
  ];

  return (
    <nav className="menu">
      <ul>
        {menuItems.map((menu) => (
          <MenuItem
            key={menu}
            label={menu}
            isActive={activeMenu === menu}
            onClick={() => onMenuClick(menu)}
          />
        ))}
      </ul>
    </nav>
  );
};

export default Menu;
