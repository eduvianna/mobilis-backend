import Sequelize, { Model } from 'sequelize';

class Sensor extends Model {
  static init(sequelize) {
    super.init(
      {
        sensor_id: Sequelize.STRING,
        name: Sequelize.STRING,
        description: Sequelize.STRING,
        type: Sequelize.STRING,
      },
      {
        sequelize,
        tableName: 'sensors',
      }
    );

    return this;
  }

  static associate(model) {
    this.hasMany(model.Word, {
      foreignKey: 'sensor_id',
      sourceKey: 'sensor_id',
      as: 'words',
    });
  }
}

export default Sensor;
