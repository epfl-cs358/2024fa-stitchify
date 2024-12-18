import React, { useState } from "react";
import PatternSelection from "./pages/PatternSelection";
import PatternDownload from "./pages/components/PatternDownload";
import Menu from "./pages/components/Menu";
import FooterBar from "./pages/components/FooterBar";
import HomePage from "./pages/HomePage";
import AboutPage from "./pages/AboutPage";
import ContactPage from "./pages/ContactPage";
import CreatePattern from "./pages/CreatePattern";
import "./base.css";
import "./navbar.css";
import "./utilities.css";
import "./footer.css";
import "./buttons.css";
import "./patterns.css";
import "./homeStyles.css";
import "./aboutStyles.css";
import "./contactStyles.css";

function App() {
  const [selectedPattern, setSelectedPattern] = useState(null);
  const [activeMenu, setActiveMenu] = useState("Home");
  const [pattern, setPattern] = useState("");

  const handlePatternClick = (pattern) => {
    setSelectedPattern(pattern);
  };

  const handleMenuClick = (menu) => {
    setActiveMenu(menu);
    setSelectedPattern(null);
  };

  const handleOwnPatternClick = (pattern) => {
    setPattern(pattern);
  };

  return (
    <div className="App">
      <header className="navbar">
        <div className="logo">Stichify</div>
        <Menu activeMenu={activeMenu} onMenuClick={handleMenuClick} />
      </header>

      <main>
        {activeMenu === "Home" && <HomePage />}
        {activeMenu === "About the Project" && <AboutPage />}
        {activeMenu === "Choose Pattern" && (
          <>
            <PatternSelection handlePatternClick={handlePatternClick} />
            {selectedPattern && <PatternDownload pattern={selectedPattern} />}
          </>
        )}
        {activeMenu === "Create your Pattern" && (
          <CreatePattern handleOwnPatternClick={handleOwnPatternClick} />
        )}
        {activeMenu === "Contact" && <ContactPage />}
      </main>

      <FooterBar />
    </div>
  );
}

export default App;
