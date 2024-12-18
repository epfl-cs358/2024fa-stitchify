import React from "react";
import Content from "./components/Content";
import FeatureCard from "./components/FeatureCard";
import "../homeStyles.css";

const Home = () => {
  const features = [
    {
      icon: (
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="64"
          height="64"
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth="2"
          strokeLinecap="round"
          strokeLinejoin="round"
          className="mx-auto mb-4 text-white"
        >
          <rect x="3" y="3" width="18" height="18" rx="2" ry="2" />
          <line x1="3" y1="9" x2="21" y2="9" />
          <line x1="9" y1="21" x2="9" y2="9" />
        </svg>
      ),
      title: "Modular Design",
      description:
        "Cutting-edge, scalable architecture allowing seamless customization and future expansions.",
    },
    {
      icon: (
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="64"
          height="64"
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth="2"
          strokeLinecap="round"
          strokeLinejoin="round"
          className="mx-auto mb-4 text-white"
        >
          <path d="M16 3h5v5" />
          <path d="M8 3H3v5" />
          <path d="M12 22v-5" />
          <path d="M12 12v-5" />
          <path d="M12 7h5v5h-5z" />
          <path d="M3 12h5v5H3z" />
          <path d="M19 12h2l-5 5-5-5h2" />
        </svg>
      ),
      title: "Advanced Patterns",
      description:
        "Sophisticated multi-color and textured knitting capabilities, pushing the boundaries of textile design.",
    },
    {
      icon: (
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="64"
          height="64"
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth="2"
          strokeLinecap="round"
          strokeLinejoin="round"
          className="mx-auto mb-4 text-white"
        >
          <path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10z" />
          <path d="M12 12V7" />
          <path d="M12 17h4.5a2.5 2.5 0 0 0 0-5h-8" />
        </svg>
      ),
      title: "Open Innovation",
      description:
        "Collaborative ecosystem driving technological advancement through community-driven development.",
    },
    {
      icon: (
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="64"
          height="64"
          viewBox="0 0 24 24"
          fill="none"
          stroke="currentColor"
          strokeWidth="2"
          strokeLinecap="round"
          strokeLinejoin="round"
          className="mx-auto mb-4 text-white"
        >
          <circle cx="12" cy="12" r="10" />
          <line x1="12" y1="8" x2="12" y2="12" />
          <line x1="12" y1="16" x2="12.01" y2="16" />
        </svg>
      ),
      title: "Intelligent Control",
      description:
        "Advanced microcontroller integration with real-time adaptive algorithms and precision control.",
    },
  ];

  return (
    <div className="App">
      <header className="bg-gradient-to-r from-teal-600 to-blue-800 text-white py-24 text-center">
        <div className="container mx-auto px-4">
          <h1 className="text-6xl font-extrabold mb-8 tracking-tight leading-none animate-gradient-text">
            Stitchify: Textile Robotics
          </h1>
          <p className="text-2xl max-w-3xl mx-auto text-white/80 font-light">
            Revolutionizing textile manufacturing through intelligent robotics,
            cutting-edge design algorithms, and seamless digital-physical
            integration
          </p>
        </div>
      </header>

      <main>
        <Content title="Project Vision">
          <div className="max-w-4xl mx-auto bg-white p-12 rounded-2xl shadow-2xl">
            <p className="text-gray-700 mb-6 leading-relaxed text-lg">
              Stitchify represents a groundbreaking convergence of robotics,
              artificial intelligence, and textile design. Our autonomous
              knitting robot transcends traditional manufacturing boundaries,
              offering unprecedented precision, creativity, and scalability.
            </p>
            <p className="text-gray-700 leading-relaxed text-lg">
              By integrating advanced microcontroller technologies,
              sophisticated stepper motor systems, and an intuitive web
              interface, we're not just building a machine—we're crafting a new
              paradigm of digital craftsmanship.
            </p>
          </div>
        </Content>

        <Content title="Core Technologies">
          <div className="grid md:grid-cols-4 gap-8">
            {features.map((feature, index) => (
              <FeatureCard
                key={index}
                icon={feature.icon}
                title={feature.title}
                description={feature.description}
              />
            ))}
          </div>
        </Content>
      </main>
    </div>
  );
};

export default Home;
