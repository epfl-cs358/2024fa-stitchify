import React from "react";
import Content from "./components/Content";
import "../aboutStyles.css";
import "./components/contentStyles.css";

function About() {
  return (
    <div className="about-container">
      <header className="text-center mb-3">
        <h1 className="max-w-4xl mx-auto bg-white p-12 rounded-2xl shadow-2xl">
          Stitchify: Knitting Robot Project
        </h1>
      </header>

      <Content title="Project Overview">
        <div className="max-w-4xl mx-auto bg-white p-12 rounded-2xl shadow-2xl">
          <p className="text-gray-700 mb-6 leading-relaxed text-lg">
            An innovative robotic initiative transforming textile manufacturing
            through Arduino-powered technology and intelligent automation.
          </p>
        </div>
      </Content>

      <Content title="Innovative Team">
        <div className="about-section-content">
          <div className="team-grid">
            <div className="team-member">
              <h4>Wiktoria Rozkosz</h4>
            </div>
            <div className="team-member">
              <h4>Bogdan Cîrje</h4>
            </div>
            <div className="team-member">
              <h4>Imane Raihane</h4>
            </div>
            <div className="team-member">
              <h4>Lorie Xu</h4>
            </div>
            <div className="team-member">
              <h4>Yasmine Hidri</h4>
            </div>
            <div className="team-member">
              <h4>Victor Zablocki</h4>
            </div>
          </div>
        </div>
      </Content>

      <Content title="Project Objectives">
        <div className="about-section-content">
          <ul className="objectives-list">
            <li>
              <strong>Technical Innovation</strong>
              <p>
                Develop an Arduino-based knitting robot with precision
                manufacturing capabilities.
              </p>
            </li>
            <li>
              <strong>Accessibility</strong>
              <p>
                Create an affordable, open-source solution for textile
                technology.
              </p>
            </li>
            <li>
              <strong>Educational Impact</strong>
              <p>
                Provide insights into robotics, embedded systems, and textile
                engineering.
              </p>
            </li>
          </ul>
        </div>
      </Content>

      <Content title="Technical Architecture">
        <div className="about-section-content">
          <div className="tech-stack">
            <div className="tech-item">
              <h4>Microcontrollers</h4>
              <p>Arduino UNO, ESP32</p>
            </div>
            <div className="tech-item">
              <h4>Mechanics</h4>
              <p>Stepper Motors</p>
            </div>
            <div className="tech-item">
              <h4>Software</h4>
              <p>React Interface</p>
            </div>
            <div className="tech-item">
              <h4>Communication</h4>
              <p>Wireless Monitoring</p>
            </div>
          </div>
        </div>
      </Content>

      <Content title="Future Roadmap">
        <div className="about-section-content">
          <ul className="roadmap-list">
            <li>
              <span className="roadmap-phase">Phase 1</span>
              <p>
                Prototype Development: Core robotic mechanism and initial
                algorithms
              </p>
            </li>
            <li>
              <span className="roadmap-phase">Phase 2</span>
              <p>
                Advanced Integration: Pattern creation and connectivity
                improvements
              </p>
            </li>
            <li>
              <span className="roadmap-phase">Phase 3</span>
              <p>
                Community Expansion: Open-source release and collaborative
                development
              </p>
            </li>
          </ul>
        </div>
      </Content>
    </div>
  );
}

export default About;
