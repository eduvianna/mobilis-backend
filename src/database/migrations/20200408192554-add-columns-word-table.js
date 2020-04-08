'use strict';

module.exports = {
  up: (queryInterface, Sequelize) => {
    return Promise.all([
      queryInterface.addColumn('word', 'name', {
        type: Sequelize.STRING,
        allowNull: false,
      }),
      queryInterface.addColumn('word', 'alarm', {
        type: Sequelize.BOOLEAN,
        allowNull: false,
      }),
    ]);
  },

  down: (queryInterface, Sequelize) => {
    return Promise.all([
      queryInterface.removeColumn('word', 'name'),
      queryInterface.removeColumn('word', 'alarm'),
    ]);
  },
};
