module.exports = {
  up: (queryInterface, Sequelize) => {
    return queryInterface.createTable('word', {
      id: {
        type: Sequelize.INTEGER,
        autoIncrement: true,
        primaryKey: true,
        allowNull: false,
      },
      sensor_id: {
        type: Sequelize.STRING,
        references: { model: 'sensors', key: 'sensor_id' },
        onUpdate: 'CASCADE',
        onDelete: 'SET NULL',
      },
      word: {
        type: Sequelize.INTEGER,
        allowNull: false,
      },
      created_at: {
        type: Sequelize.DATE,
        allowNull: false,
      },
      updated_at: {
        type: Sequelize.DATE,
        allowNull: false,
      },
    });
  },

  down: queryInterface => {
    return queryInterface.dropTable('word');
  },
};
